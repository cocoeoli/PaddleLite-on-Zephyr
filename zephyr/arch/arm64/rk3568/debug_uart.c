#define Use_debug_earlyprint

#include "rk3568_common.h"
#include "include/mm.h"
#include <zephyr/arch/arm64/debug_uart.h>
#include <zephyr/kernel.h>

#include <kernel_internal.h>

#define MY_GET_EL(mode)		(((mode) >> 0x02) & 0x03)
static inline unsigned int get_current_el(void)
{
	return MY_GET_EL(read_currentel());
}

#ifdef Use_debug_earlyprint
	#include "stdarg.h"
	#define  MAX_NUMBER_BYTES  64
	int debug_earlyprint(const char *fmt, ...);
	int debug_earlyprint_test(void);

	const unsigned char hex_tab[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	int getCmdLine();
	void miniShell();
	int strCmp(const char*s1, const char* s2);
	int strNotEqual(const char*s1, const char* s2);
	int strEqual(const char*s1, const char* s2);
	int str2num(const unsigned char *s, int strBufferLen);
	extern int strIsWhiteSpace(char c);
	void strClear(unsigned char* s, int len, char cFill);
	void strCpy(const unsigned char* src, int srcLen, unsigned char * dst, int dstBufferSize);
	void hexDump(const char* buf, int len);

#endif

K_KERNEL_STACK_DEFINE(earlyprint_stack, PRINTK_STACK_SIZE);

extern u8 BootromContex;
void save_boot_params_ret(void);
int setjmp(u8* ctx);
void longjmp(u8* ctx, int ret);
void printascii(const char *str);

u32 boot_mode, boot_dvid;
u32 bootrom_action;

extern void __start_zephyr();


/*************************************************/

int save_boot_params(void)
{
#define IRAM_START_ADDR					0xfdcc0000
#define BROM_BOOTSOURCE_ID_ADDR 		(IRAM_START_ADDR + 0x10)
#define CONFIG_ROCKCHIP_BOOT_MODE_REG	0xfdc20200 // 0xfdc20000 + 0x200  (PMU_GRF + PMU_GRF_OS_REG0)

#define BROMA_GOTO_NEXT	0
#define BROMA_RELOAD_ME	1


	int tmp = setjmp(&BootromContex);  // setjmp 首次返回0， 当在别的地方调用 longjmp(brom_ctx, 整数n) 时 setjmp 会再次从这里开始往运行，返回的 tmp 值为 整数n！
	
	if(0 == tmp)
	{
		// contex saved in setjmp(&BootromContex) & return 0;
		
		boot_mode = readl(CONFIG_ROCKCHIP_BOOT_MODE_REG);
		boot_dvid = readl(BROM_BOOTSOURCE_ID_ADDR);
		bootrom_action = BROMA_GOTO_NEXT;
		
		save_boot_params_ret(); // 不让这个函数结束，实际就是从 rk3568tpl_start.S 中的 save_boot_params_ret 处接着往下运行
	}else{
		printascii("longjpm ok.\r\n");

		return bootrom_action;
	}
	
	// 这里开始的代码，不会被执行！因为根本不会运行到这里！
	return 2;
}

void back_to_bootrom(int exitCode)
{
	bootrom_action = exitCode;

	longjmp(&BootromContex, 888888);
}


void uart_init()
{
#define SYS_GRF					0xFDC60000
#define 	GRF_IOFUNC_SEL3		0x030C

#define PMU_GRF					0xfdc20000
#define 	GRF_GPIO0D_IOMUX_L	0x0018

#define CONFIG_DEBUG_UART_BASE 0xFE660000
#define CONFIG_DEBUG_UART_CLOCK 24000000
#define CONFIG_BAUDRATE 1500000

	// IOMUX 配置，将UART2对应的GPIO引脚选用为 uart2 mux0 功能
	//*((u32 *)(SYS_GRF + GRF_IOFUNC_SEL3))		= 0x0C000000;
	rk_clrsetreg(SYS_GRF + GRF_IOFUNC_SEL3, 0x0C00, 0x0000);
	
	// GPIO0_D0 做 uart2 mux0 的 rx 线， GPIO0_D1 做 uart2 mux0 的 tx 线
	//*((u32 *)(PMU_GRF + GRF_GPIO0D_IOMUX_L))	= 0x00770011;
	rk_clrsetreg(PMU_GRF + GRF_GPIO0D_IOMUX_L, 0x0077, 0x0011);

	// 时钟频率与波特率换算？？
	int baud_divisor = DIV_ROUND_CLOSEST(CONFIG_DEBUG_UART_CLOCK, 16 * CONFIG_BAUDRATE);
	
	
	struct NS16550 *com_port = (struct NS16550 *)CONFIG_DEBUG_UART_BASE;
	serial_dout(&com_port->ier, (1 << 6));
	serial_dout(&com_port->mcr, 0x03);
	serial_dout(&com_port->fcr, 0x07);

	serial_dout(&com_port->lcr, 0x80 | 0x03);
	serial_dout(&com_port->dll, baud_divisor & 0xff);
	serial_dout(&com_port->dlm, (baud_divisor >> 8) & 0xff);
	serial_dout(&com_port->lcr, 0x03);

}

static void putc(int ch)
{
	if (ch == '\n') putc('\r');
	
	struct NS16550 *com_port;

	com_port = (struct NS16550 *)CONFIG_DEBUG_UART_BASE;

	while (!(serial_din(&com_port->lsr) & 0x20))
		;
	serial_dout(&com_port->thr, ch);
}

static int getc(void)
{
	struct NS16550 *com_port;

	com_port = (struct NS16550 *)CONFIG_DEBUG_UART_BASE;

	while (!(serial_din(&com_port->lsr) & 0x01))
		;

	return serial_din(&com_port->rbr);
}

void printascii(const char *str)
{
	while (*str) putc(*str++);
}



void do_irq(void)
{
}

static void static_delay(int nSecondWait)
{
	if(nSecondWait < 0) return;

	volatile unsigned long int i,j;
	for(i=nSecondWait;i>0;i--)
		for(j=800000;j>0;j--);
}

static void asm_register_print(void)
{

	switch(get_current_el()){
	case 2: {
		debug_earlyprint("sctlr_el2:\t 0x%08x-%08x,\t spsr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_sctlr_el2()>>32),read_sctlr_el2(), (unsigned long)(read_spsr_el2()>>32), read_spsr_el2());
		debug_earlyprint("mair_el2:\t 0x%08x-%08x,\t tcr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_mair_el2()>>32),read_mair_el2(), (unsigned long)(read_tcr_el2()>>32),read_tcr_el2());
		debug_earlyprint("vtcr_el2:\t 0x%08x-%08x,\t vttbr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_vtcr_el2()>>32), read_vtcr_el2(), (unsigned long)(read_vttbr_el2()>>32), read_vttbr_el2());
		debug_earlyprint("tpidr_el2:\t 0x%08x-%08x,\t ttbr0_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_tpidr_el2()>>32), read_tpidr_el2(), (unsigned long)(read_ttbr0_el2()>>32), read_ttbr0_el2());
		debug_earlyprint("vbar_el2:\t 0x%08x-%08x,\t mpidr_el1:\t 0x%08x-%08x  \r\n", (unsigned long)(read_vbar_el2()>>32), read_vbar_el2(), (unsigned long)(read_mpidr_el1()>>32), read_mpidr_el1());
		debug_earlyprint("cptr_el2:\t 0x%08x-%08x,\t hcr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_cptr_el2()>>32), read_cptr_el2(), (unsigned long)(read_hcr_el2()>>32), read_hcr_el2());
		debug_earlyprint("esr_el2:\t 0x%08x-%08x,\t elr_el2:\t 0x%08x-%08x \r\n", (unsigned long)(read_esr_el2()>>32), read_esr_el2(), (unsigned long)(read_elr_el2()>>32),read_elr_el2());
	}
	case 1: {
		debug_earlyprint("sctlr_el1:\t 0x%08x-%08x,\t spsr_el1:\t 0x%08x-%08x  \r\n", (unsigned long)(read_sctlr_el1()>>32),read_sctlr_el1(), (unsigned long)(read_spsr_el1()>>32),read_spsr_el1());
		debug_earlyprint("mair_el1:\t 0x%08x-%08x,\t tcr_el1:\t 0x%08x-%08x  \r\n", (unsigned long)(read_mair_el1()>>32),read_mair_el1(), (unsigned long)(read_tcr_el1()>>32),read_tcr_el1());
		debug_earlyprint("ttbr0_el1:\t 0x%08x-%08x,\t ttbr1_el1:\t 0x%08x-%08x  \r\n", (unsigned long)(read_ttbr0_el1()>>32),read_ttbr0_el1(), (unsigned long)(read_ttbr1_el1()>>32),read_ttbr1_el1());
		debug_earlyprint("mpidr_el1:\t 0x%08x-%08x,\t cpacr_el1:\t 0x%08x-%08x \r\n",  (unsigned long)(read_mpidr_el1()>>32),read_mpidr_el1(), (unsigned long)(read_cpacr_el1()>>32),read_cpacr_el1());
		debug_earlyprint("esr_el1:\t 0x%08x-%08x,\t elr_el1:\t 0x%08x-%08x \r\n",  (unsigned long)(read_esr_el1()>>32),read_esr_el1(), (unsigned long)(read_elr_el1()>>32),read_elr_el1());
		debug_earlyprint("isr_el1:\t 0x%08x-%08x,\t \r\n",  (unsigned long)(read_isr_el1()>>32),read_isr_el1());
		break;
	}
	default:
		printascii("Wrong exception mode! \n");
		break;
	}
	return;
}

void asm_register_print_smp(unsigned long long reg0, unsigned long long reg1)
{
	unsigned long reg0_1, reg1_1;

	reg0_1 = reg0 >> 32;
	reg1_1 = reg1 >> 32;
	printk("x0: 0x%08x-%08x , x1: 0x%08x-%08x  \r\n", reg0_1, reg0, reg1_1, reg1);

	switch(get_current_el()){
	case 2: {
		printk("sctlr_el2:\t 0x%08x-%08x,\t spsr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_sctlr_el2()>>32),read_sctlr_el2(), (unsigned long)(read_spsr_el2()>>32), read_spsr_el2());
		printk("mair_el2:\t 0x%08x-%08x,\t tcr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_mair_el2()>>32),read_mair_el2(), (unsigned long)(read_tcr_el2()>>32),read_tcr_el2());
		printk("vtcr_el2:\t 0x%08x-%08x,\t vttbr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_vtcr_el2()>>32), read_vtcr_el2(), (unsigned long)(read_vttbr_el2()>>32), read_vttbr_el2());
		printk("tpidr_el2:\t 0x%08x-%08x,\t ttbr0_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_tpidr_el2()>>32), read_tpidr_el2(), (unsigned long)(read_ttbr0_el2()>>32), read_ttbr0_el2());
		printk("vbar_el2:\t 0x%08x-%08x,\t mpidr_el1:\t 0x%08x-%08x  \r\n", (unsigned long)(read_vbar_el2()>>32), read_vbar_el2(), (unsigned long)(read_mpidr_el1()>>32), read_mpidr_el1());
		printk("cptr_el2:\t 0x%08x-%08x,\t hcr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_cptr_el2()>>32), read_cptr_el2(), (unsigned long)(read_hcr_el2()>>32), read_hcr_el2());
		printk("esr_el2:\t 0x%08x-%08x\r\n", (unsigned long)(read_esr_el2()>>32), read_esr_el2());
	}
	case 1: {
		printk("sctlr_el1:\t 0x%08x-%08x,\t spsr_el1:\t 0x%08x-%08x  \r\n", (unsigned long)(read_sctlr_el1()>>32),read_sctlr_el1(), (unsigned long)(read_spsr_el1()>>32),read_spsr_el1());
		printk("mair_el1:\t 0x%08x-%08x,\t tcr_el1:\t 0x%08x-%08x  \r\n", (unsigned long)(read_mair_el1()>>32),read_mair_el1(), (unsigned long)(read_tcr_el1()>>32),read_tcr_el1());
		printk("ttbr0_el1:\t 0x%08x-%08x,\t ttbr1_el1:\t 0x%08x-%08x  \r\n", (unsigned long)(read_ttbr0_el1()>>32),read_ttbr0_el1(), (unsigned long)(read_ttbr1_el1()>>32),read_ttbr1_el1());
		printk("mpidr_el1:\t 0x%08x-%08x,\t cpacr_el1:\t 0x%08x-%08x \r\n",  (unsigned long)(read_mpidr_el1()>>32),read_mpidr_el1(), (unsigned long)(read_cpacr_el1()>>32),read_cpacr_el1());
		printk("esr_el1:\t 0x%08x-%08x,\t elr_el1:\t 0x%08x-%08x \r\n",  (unsigned long)(read_esr_el1()>>32),read_esr_el1(), (unsigned long)(read_elr_el1()>>32),read_elr_el1());
		printk("isr_el1:\t 0x%08x-%08x,\t tpidrro_el0:\t 0x%08x-%08x\r\n",  (unsigned long)(read_isr_el1()>>32),read_isr_el1(), (unsigned long)(read_tpidrro_el0()>>32),read_tpidrro_el0());
		break;
	}
	default:
		printascii("Wrong exception mode! \n");
		break;
	}	
	return;
}

static void show_boot_mode(void)
{
	printascii("**********************************");
	printascii("\n## Booting on uboot......");
	printascii("\n## Earlyprintk init successful!");
	switch(get_current_el()){
	case 2: {
		printascii("\n## Boot system on EL2 mode!\n");
		break;
	}
	case 1: {
		printascii("\n## Boot system on EL1 mode!\n");
		break;
	}
	default:
		printascii("Boot Wrong mode! \n");
		break;
	}	
	return;
}

void print_uart_regs(void)
{
	unsigned int reg_value;
	struct NS16550 *com_port;

	com_port = (struct NS16550 *)CONFIG_DEBUG_UART_BASE;

	reg_value = serial_din(&com_port->fcr);
	debug_earlyprint("reg_value: 0x%08x-%08x \n", reg_value>>32, reg_value);

	return serial_din(&com_port->rbr);	
}

void early_print_debug(unsigned long long reg1, unsigned long long reg2)
{
	unsigned long reg1_1, reg2_1;

	reg1_1 = reg1 >> 32;
	reg2_1 = reg2 >> 32;
	debug_earlyprint("x0: 0x%08x-%08x , x1: 0x%08x-%08x  \r\n", reg1_1, reg1, reg2_1, reg2);
//	asm_register_print();
	return;
}

/* 构造一个全局数据结构来存储所有的字符串！ */
#define reg_per		13
uint64_t debug_print_reg[10000];
int count_offset=2;

static void asm_register_print_delay(void)
{

	switch(get_current_el()){
	case 2: {
		debug_earlyprint("sctlr_el2:\t 0x%08x-%08x,\t spsr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_sctlr_el2()>>32),read_sctlr_el2(), (unsigned long)(read_spsr_el2()>>32), read_spsr_el2());
		debug_earlyprint("mair_el2:\t 0x%08x-%08x,\t tcr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_mair_el2()>>32),read_mair_el2(), (unsigned long)(read_tcr_el2()>>32),read_tcr_el2());
		debug_earlyprint("vtcr_el2:\t 0x%08x-%08x,\t vttbr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_vtcr_el2()>>32), read_vtcr_el2(), (unsigned long)(read_vttbr_el2()>>32), read_vttbr_el2());
		debug_earlyprint("tpidr_el2:\t 0x%08x-%08x,\t ttbr0_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_tpidr_el2()>>32), read_tpidr_el2(), (unsigned long)(read_ttbr0_el2()>>32), read_ttbr0_el2());
		debug_earlyprint("vbar_el2:\t 0x%08x-%08x,\t mpidr_el1:\t 0x%08x-%08x  \r\n", (unsigned long)(read_vbar_el2()>>32), read_vbar_el2(), (unsigned long)(read_mpidr_el1()>>32), read_mpidr_el1());
		debug_earlyprint("cptr_el2:\t 0x%08x-%08x,\t hcr_el2:\t 0x%08x-%08x  \r\n", (unsigned long)(read_cptr_el2()>>32), read_cptr_el2(), (unsigned long)(read_hcr_el2()>>32), read_hcr_el2());
		debug_earlyprint("esr_el2:\t 0x%08x-%08x\r\n", (unsigned long)(read_esr_el2()>>32), read_esr_el2());
	}
	case 1: {
		debug_print_reg[count_offset++] = read_sctlr_el1();
		debug_print_reg[count_offset++] = read_spsr_el1();
		debug_print_reg[count_offset++] = read_mair_el1();
		debug_print_reg[count_offset++] = read_tcr_el1();
		debug_print_reg[count_offset++] = read_ttbr0_el1();
		debug_print_reg[count_offset++] = read_ttbr1_el1();
		debug_print_reg[count_offset++] = read_mpidr_el1();
		debug_print_reg[count_offset++] = read_cpacr_el1();
		debug_print_reg[count_offset++] = read_esr_el1();
		debug_print_reg[count_offset++] = read_elr_el1();
		debug_print_reg[count_offset++] = read_isr_el1();
		break;
	}
	default:
		printascii("Wrong exception mode! \n");
		break;
	}	
	return;
}

void early_print_debug_delay(unsigned long long reg1, unsigned long long reg2)
{
	if(count_offset > 9800)
		debug_earlyprint("Error, reg string too long! count:%d \n", count_offset);

	debug_print_reg[count_offset++] = reg1;
	debug_print_reg[count_offset++] = reg2;

	asm_register_print_delay();
	return;
}

void show_print_debug_delay(void)
{
	int j;
	while(count_offset>0){
		for(j=count_offset-reg_per; j<count_offset; j+=2){
			debug_earlyprint("Reg-%d: \t 0x%08x-%08x,\t Reg-%d: \t 0x%08x-%08x  \r\n", j+reg_per-count_offset, 
				(unsigned long)(debug_print_reg[j]>>32),debug_print_reg[j], j+1+reg_per-count_offset,(unsigned long)(debug_print_reg[j+1]>>32), debug_print_reg[j+1]);
		}
		debug_earlyprint("---------------------------------------\n");
	count_offset -= reg_per;
	}
}

void show_step_debug(void)
{
	printascii("Enter the exception! \n");
}

int tpl_main(void)
{
	unsigned long long times = 0;
	uart_init();

	show_boot_mode();

	return 0;

#ifdef Use_debug_earlyprint
	hexDump((u8*)0xffff0000, 32);
	//miniShell();
	return 0;
	__start_zephyr();
#else
	char c;

	do{
		c = (unsigned char)getc();
		if(c == 'q')
		{
			putc(c);
			printascii("\r\nexiting...\r\n");

			back_to_bootrom(1);
			return 0;
		}else{
			putc(c);
			printascii("\r\n");
		}
	}while(1);
#endif

	static_delay(2); // 等待约2秒后

	return 1;
}

#ifdef Use_debug_earlyprint

/********************* debug_earlyprint **************************/

static int outc(int c)
{
    putc(c);
    return 0;
}

static int outs (const char *s)
{
    while (*s != '\0')
        putc(*s++);
    return 0;
}

static int out_num(long n, int base, char lead, int maxwidth)
{
    unsigned long m = 0;
    char buf[MAX_NUMBER_BYTES], *s = buf + sizeof(buf);
    int count = 0, i = 0;

    *--s = '\0';

    if (n < 0)
        m = -n;
    else
        m = n;

    do
    {
        *--s = hex_tab[m % base];
        count++;
    }
    while ((m /= base) != 0);

    if( maxwidth && count < maxwidth)
    {
        for (i = maxwidth - count; i; i--)
            *--s = lead;
    }

    if (n < 0)
        *--s = '-';

    return outs(s);
}


/*ref: int vdebug_earlyprint(const char *format, va_list ap); */
static int my_vdebug_earlyprint(const char *fmt, va_list ap)
{
    char lead = ' ';
    int  maxwidth = 0;

    for(; *fmt != '\0'; fmt++)
    {
        if (*fmt != '%')
        {
            outc(*fmt);
            continue;
        }
        lead = ' ';
        maxwidth = 0;

        //format : %08d, %8d,%d,%u,%x,%f,%c,%s
        fmt++;
        if(*fmt == '0')
        {
            lead = '0';
            fmt++;
        }

        while(*fmt >= '0' && *fmt <= '9')
        {
            maxwidth *= 10;
            maxwidth += (*fmt - '0');
            fmt++;
        }

        switch (*fmt)
        {
        case 'd':
            out_num(va_arg(ap, int),          10, lead, maxwidth);
            break;
        case 'o':
            out_num(va_arg(ap, unsigned int),  8, lead, maxwidth);
            break;
        case 'u':
            out_num(va_arg(ap, unsigned int), 10, lead, maxwidth);
            break;
        case 'x':
            out_num(va_arg(ap, unsigned int), 16, lead, maxwidth);
            break;
        case 'c':
            outc(va_arg(ap, int   ));
            break;
        case 's':
            outs(va_arg(ap, char *));
            break;

        default:
            outc(*fmt);
            break;
        }
    }
    return 0;
}

//ref: int debug_earlyprint(const char *format, ...);
int debug_earlyprint(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    my_vdebug_earlyprint(fmt, ap);
    va_end(ap);
    return 0;
}

int debug_earlyprint_test(void)
{
    debug_earlyprint("=========This is debug_earlyprint test=========\r\n");
    debug_earlyprint("test char            = %c,%c\r\n", 'H', 'c');
    debug_earlyprint("test decimal1 number = %d\r\n",     123456);
    debug_earlyprint("test decimal2 number = %d\r\n",     -123456);
    debug_earlyprint("test hex1    number  = 0x%x\r\n",   0x123456);
    debug_earlyprint("test hex2    number  = 0x%08x\r\n", 0x123456);
    debug_earlyprint("test string          = %s\r\n",    "debug_earlyprint code copy from: www.hceng.cn");

    return 0;
}


void hexDump(const char* buf, int len)
{
	if (len < 1 || buf == 0) return;
 
	const char *hexChars = "0123456789ABCDEF";
	int i = 0;
	char c = 0x00;
	char str_print_able[17];
	char str_hex_buffer[16 * 3 + 1];
 
	for (i = 0; i < (len / 16) * 16; i += 16)
	{
		int j = 0;
		for (j = 0; j < 16; j++)
		{
			c = buf[i + j];
 
			// hex
			int z = j * 3;
			str_hex_buffer[z++] = hexChars[(c >> 4) & 0x0F];
			str_hex_buffer[z++] = hexChars[c & 0x0F];
			str_hex_buffer[z++] = (j < 10 && !((j + 1) % 8)) ? '_' : ' ';
 
			// string with space repalced
			if (c < 32 || c == '\0' || c == '\t' || c == '\r' || c == '\n' || c == '\b')
				str_print_able[j] = '.';
			else
				str_print_able[j] = c;
		}
		str_hex_buffer[16 * 3] = 0x00;
		str_print_able[j] = 0x00;
 
		debug_earlyprint("%04x  %s %s\n", i, str_hex_buffer, str_print_able);
	}
 
	// 处理剩下的不够16字节长度的部分
	int leftSize = len % 16;
	if (leftSize < 1) return;
	int j = 0;
	int pos = i;
	for (; i < len; i++)
	{
		c = buf[i];
 
		// hex
		int z = j * 3;
		str_hex_buffer[z++] = hexChars[(c >> 4) & 0x0F];
		str_hex_buffer[z++] = hexChars[c & 0x0F];
		str_hex_buffer[z++] = ' ';
 
		// string with space repalced
		if (c < 32 || c == '\0' || c == '\t' || c == '\r' || c == '\n' || c == '\b')
			str_print_able[j] = '.';
		else
			str_print_able[j] = c;
		j++;
	}
	str_hex_buffer[leftSize * 3] = 0x00;
	str_print_able[j] = 0x00;
 
	for (j = leftSize; j < 16; j++)
	{
		int z = j * 3;
		str_hex_buffer[z++] = ' ';
		str_hex_buffer[z++] = ' ';
		str_hex_buffer[z++] = ' ';
	}
	str_hex_buffer[16 * 3] = 0x00;
	debug_earlyprint("%04x  %s %s\n", pos, str_hex_buffer, str_print_able);

}


/********************* miniShell **************************/
#define MAX_CMD_BUFFER_SIZE 256
#define MAX_ARG_BUFFER_SIZE 256
#define MAX_ARG_COUNT__SIZE 5

static unsigned char   cmdBuffer[MAX_CMD_BUFFER_SIZE];
static unsigned char   argBuffer[MAX_ARG_BUFFER_SIZE];
static int argOffset = 0;

typedef struct {
	const char* pStr;
	int len;
}shellArg;
static shellArg args[MAX_ARG_COUNT__SIZE];

int getCmdLine()
{
	int i;
	char c;

	i=0;
	do{
		 c = (unsigned char)(getc());
		 if(c == '\n')
		 {
			continue;
		 }
		 if(c == '\r')
		 {
			break;
		 }
		 if(c == '\b')
		 {
			if(i>0)
			{
				putc(c);
				i--;
				cmdBuffer[i] = '\0';
			}
			continue;
		 }

		 putc(c);

		 cmdBuffer[i] = c;
		 cmdBuffer[i+1] = '\0';
		 i++;

		 if(i >= (MAX_CMD_BUFFER_SIZE - 1) ) break;
	}while(1);

	return i;
}

int splitCmdString()
{
	const char* strCmd = cmdBuffer;
	int argBeginAt = 0;
	int argLength = 0;
	int nArgs = 0;

	do{
		//skipWhiteSpace;
		while(argOffset < MAX_CMD_BUFFER_SIZE &&  *strCmd != 0 && strIsWhiteSpace(strCmd[argOffset]) ) argOffset++;
		if(argOffset >= MAX_CMD_BUFFER_SIZE || *strCmd == 0) break;
		args[nArgs].pStr = strCmd + argOffset;

		// skip no-whitespace
		while(argOffset < MAX_CMD_BUFFER_SIZE &&  *strCmd != 0 && !strIsWhiteSpace(strCmd[argOffset]) ) argOffset++;
		args[nArgs].len = (int)((strCmd + argOffset) - args[nArgs].pStr);

		nArgs ++;
	}while(1);

	return nArgs;
}

void miniShell()
{
	int nArgs = 0;


	printascii("\r\n");
	printascii("type help for more infomation\r\n");

	do {
		printascii("shell#");
		if(getCmdLine() > 0)
		{
			argOffset = 0;
			nArgs = splitCmdString();
			if(nArgs > 0)
			{
				strCpy(args[0].pStr, args[0].len, argBuffer, MAX_ARG_BUFFER_SIZE);

				if(strEqual(argBuffer, "help")){
					printascii("\r\n type exit to back_to_bootrom\r\n type hexdump to dump 1kb memory @ 0xffff0000\r\n no more content...\r\n");
					debug_earlyprint(" gcc magic variables \"__func__\":%s\r\n\r\n", __func__); // gcc 的魔幻变量，取当前函数名称
				}else if(strEqual(argBuffer, "exit") || strEqual(argBuffer, "quit") || strEqual(argBuffer, "q")){
					int exitCode = BROMA_GOTO_NEXT;
					if(nArgs >1 )
					{
						exitCode = str2num(args[1].pStr, args[1].len);
					}

					debug_earlyprint("\r\nexit now with exitCode: %d\r\n", exitCode);
					printascii("NOTE: Bootrom will retry for 5 times\r\n\r\n");

					back_to_bootrom(exitCode);
					//return;
					break;
				}else if(strEqual(argBuffer, "hexdump")){
					printascii("\r\n");
					const char* buf = (const char*)0xffff0000;
					hexDump(buf, 1024*1);
				}else {
					printascii("\r\n");
					printascii((const char*)cmdBuffer);
					printascii("\r\n");
				}
			}else{
				printascii("\r\n");
				printascii((const char*)cmdBuffer);
				printascii("\r\n");
			}
		}else{
			printascii("\r\n");
		}
	}while(1);
}


inline int strIsWhiteSpace(char c)
{
	/*
	return value define:
	is: 1
	others: 0
	*/
	if(c==' ' || c == '\t') return 1;
	return 0;
}

int strCmp(const char*s1, const char* s2)
{
	/*
		eq = 0
		ne = -1;
	*/
	
	if(s1 == 0 && s2 == 0) return 0;
	if(s1 == 0 || s2 == 0) return -1;
	
	char* src = (char*)s1;
	char* dst = (char*)s2;
	
	do{
		char c1 = *src++;
		char c2 = *dst++;
		
		if( ( c1 && !c2) || (c2 && !c1) ) return -1; // 有一个先到行尾
		if( !c1 && !c2) return 0; // 都到行尾
		if(c1 != c2) return -1; // 都没到行尾，比较之，不一样，返回不相等
		// 不然就是相等的
	}
	while(1);
}

int strNotEqual(const char*s1, const char* s2)
{
	return strCmp(s1, s2);
}

int strEqual(const char*s1, const char* s2)
{
	return !strCmp(s1, s2);
}

int str2num(const unsigned char *s, int strBufferLen)
{
	if(strBufferLen < 1) return 0;
	
	int i=0;
	int rlt = 0;
	char c = 0;
	char sign = '+';
	for(i=0; i<=strBufferLen; i++){
		c = s[i];
		if(strIsWhiteSpace(c)) continue;
		if(c == '+') continue;
		if(c == '-') {sign = '-'; continue;}
		if(c <'0' || c>'9') break;
		
		rlt = 10*rlt + (c -'0');
	};
	
	
	return sign == '+'?rlt:(rlt * -1);
}

void strClear(unsigned char* s, int len, char cFill)
{
	int i;
	for(i=0; i< len; i++) s[i] = cFill;
}

void strCpy(const unsigned char* src, int srcLen, unsigned char * dst, int dstBufferSize)
{
	int i;
	for(i=0; i < srcLen; i++)
	{
		if(i>= (dstBufferSize -1 )) break;
		dst[i] = src[i];
	}
	dst[i] = 0;
}

#endif
