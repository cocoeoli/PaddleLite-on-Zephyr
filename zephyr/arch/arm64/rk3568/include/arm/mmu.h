#ifndef _MMU_H
#define _MMU_H

#include <arch/arm64/arm_mmu.h>

#define MM_TYPE_PAGE_TABLE		0x3
#define MM_TYPE_PAGE 			0x3
#define MM_TYPE_BLOCK			0x1
#define MM_ACCESS			(0x1 << 10)
#define MM_ACCESS_PERMISSION		(0x01 << 6) 

/*
 * Memory region attributes:
 *
 *   n = AttrIndx[2:0]
 *			n	MAIR
 *   DEVICE_nGnRnE	000	00000000
 *   NORMAL_NC		001	01000100
 */
#define MT_DEVICE_nGnRnE_FLAGS		0x00
#define MT_NORMAL_NC_FLAGS  		0x44
#define MAIR_VALUE			 (0x44 << (8 * 3U))

#define MMU_FLAGS	 		(MM_TYPE_BLOCK | (MT_NORMAL_NC << 2) | MM_ACCESS)	
#define MMU_DEVICE_FLAGS		(0x1 | MM_ACCESS)	
#define MMU_PTE_FLAGS			(MM_TYPE_PAGE | (MT_NORMAL_NC << 2) | MM_ACCESS | MM_ACCESS_PERMISSION)	

#define TCR_T1SZ			((64 - 48) << 16)
#define TCR_TG1_4K			(2UL << 30)
#define TCR_VALUE			((64 - 48) | ((64 - 48) << 16)  | (2UL << 30))

#endif
