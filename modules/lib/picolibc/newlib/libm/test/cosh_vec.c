/*
 * Copyright (c) 1994 Cygnus Support.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * and/or other materials related to such
 * distribution and use acknowledge that the software was developed
 * at Cygnus Support, Inc.  Cygnus Support, Inc. may not be used to
 * endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
#include "test.h"
 one_line_type cosh_vec[] = {
{62, 0,123,__LINE__, 0x3ffcf871, 0xf8dfa800, 0xbff33333, 0x33333333},	/* 1.81066=f(-1.2)*/
{63, 0,123,__LINE__, 0x3ffcbafc, 0xca475e20, 0xbff30a3d, 0x70a3d70a},	/* 1.79565=f(-1.19)*/
{63, 0,123,__LINE__, 0x3ffc7e43, 0xe5bb3dd7, 0xbff2e147, 0xae147ae1},	/* 1.78083=f(-1.18)*/
{63, 0,123,__LINE__, 0x3ffc4245, 0xbd476b74, 0xbff2b851, 0xeb851eb8},	/* 1.76618=f(-1.17)*/
{62, 0,123,__LINE__, 0x3ffc0700, 0xc7bfd6cc, 0xbff28f5c, 0x28f5c28f},	/* 1.75171=f(-1.16)*/
{64, 0,123,__LINE__, 0x3ffbcc73, 0x80b62a84, 0xbff26666, 0x66666666},	/* 1.73741=f(-1.15)*/
{63, 0,123,__LINE__, 0x3ffb929c, 0x686fda6f, 0xbff23d70, 0xa3d70a3d},	/* 1.72329=f(-1.14)*/
{64, 0,123,__LINE__, 0x3ffb597a, 0x03dc50b7, 0xbff2147a, 0xe147ae14},	/* 1.70934=f(-1.13)*/
{64, 0,123,__LINE__, 0x3ffb210a, 0xdc8b399b, 0xbff1eb85, 0x1eb851eb},	/* 1.69557=f(-1.12)*/
{63, 0,123,__LINE__, 0x3ffae94d, 0x80a2ed81, 0xbff1c28f, 0x5c28f5c2},	/* 1.68196=f(-1.11)*/
{64, 0,123,__LINE__, 0x3ffab240, 0x82d6f90f, 0xbff19999, 0x99999999},	/* 1.66852=f(-1.1)*/
{63, 0,123,__LINE__, 0x3ffa7be2, 0x7a5ec32f, 0xbff170a3, 0xd70a3d70},	/* 1.65525=f(-1.09)*/
{63, 0,123,__LINE__, 0x3ffa4632, 0x02ec508b, 0xbff147ae, 0x147ae147},	/* 1.64214=f(-1.08)*/
{63, 0,123,__LINE__, 0x3ffa112d, 0xbca32481, 0xbff11eb8, 0x51eb851e},	/* 1.62919=f(-1.07)*/
{64, 0,123,__LINE__, 0x3ff9dcd4, 0x4c0f3f1f, 0xbff0f5c2, 0x8f5c28f5},	/* 1.61641=f(-1.06)*/
{64, 0,123,__LINE__, 0x3ff9a924, 0x5a1c3817, 0xbff0cccc, 0xcccccccc},	/* 1.60379=f(-1.05)*/
{63, 0,123,__LINE__, 0x3ff9761c, 0x940c7646, 0xbff0a3d7, 0x0a3d70a3},	/* 1.59134=f(-1.04)*/
{63, 0,123,__LINE__, 0x3ff943bb, 0xab7083c2, 0xbff07ae1, 0x47ae147a},	/* 1.57904=f(-1.03)*/
{63, 0,123,__LINE__, 0x3ff91200, 0x561e7e0b, 0xbff051eb, 0x851eb851},	/* 1.56689=f(-1.02)*/
{63, 0,123,__LINE__, 0x3ff8e0e9, 0x4e29a24b, 0xbff028f5, 0xc28f5c28},	/* 1.55491=f(-1.01)*/
{64, 0,123,__LINE__, 0x3ff8b075, 0x51d9f54f, 0xbfefffff, 0xfffffffe},	/* 1.54308=f(-1)*/
{64, 0,123,__LINE__, 0x3ff880a3, 0x23a40720, 0xbfefae14, 0x7ae147ac},	/* 1.53141=f(-0.99)*/
{63, 0,123,__LINE__, 0x3ff85171, 0x8a20d1e7, 0xbfef5c28, 0xf5c28f5a},	/* 1.51988=f(-0.98)*/
{63, 0,123,__LINE__, 0x3ff822df, 0x5005b407, 0xbfef0a3d, 0x70a3d708},	/* 1.50851=f(-0.97)*/
{64, 0,123,__LINE__, 0x3ff7f4eb, 0x441c8516, 0xbfeeb851, 0xeb851eb6},	/* 1.49729=f(-0.96)*/
{63, 0,123,__LINE__, 0x3ff7c794, 0x393bc5a7, 0xbfee6666, 0x66666664},	/* 1.48623=f(-0.95)*/
{62, 0,123,__LINE__, 0x3ff79ad9, 0x063ee98b, 0xbfee147a, 0xe147ae12},	/* 1.4753=f(-0.94)*/
{63, 0,123,__LINE__, 0x3ff76eb8, 0x85febc76, 0xbfedc28f, 0x5c28f5c0},	/* 1.46453=f(-0.93)*/
{63, 0,123,__LINE__, 0x3ff74331, 0x9749e0c6, 0xbfed70a3, 0xd70a3d6e},	/* 1.4539=f(-0.92)*/
{63, 0,123,__LINE__, 0x3ff71843, 0x1cdd683d, 0xbfed1eb8, 0x51eb851c},	/* 1.44342=f(-0.91)*/
{63, 0,123,__LINE__, 0x3ff6edeb, 0xfd5d867e, 0xbfeccccc, 0xccccccca},	/* 1.43309=f(-0.9)*/
{63, 0,123,__LINE__, 0x3ff6c42b, 0x234e5d24, 0xbfec7ae1, 0x47ae1478},	/* 1.42289=f(-0.89)*/
{64, 0,123,__LINE__, 0x3ff69aff, 0x7d0ce134, 0xbfec28f5, 0xc28f5c26},	/* 1.41284=f(-0.88)*/
{63, 0,123,__LINE__, 0x3ff67267, 0xfcc7d9d1, 0xbfebd70a, 0x3d70a3d4},	/* 1.40293=f(-0.87)*/
{62, 0,123,__LINE__, 0x3ff64a63, 0x9878f7ea, 0xbfeb851e, 0xb851eb82},	/* 1.39316=f(-0.86)*/
{63, 0,123,__LINE__, 0x3ff622f1, 0x49de06d2, 0xbfeb3333, 0x33333330},	/* 1.38353=f(-0.85)*/
{62, 0,123,__LINE__, 0x3ff5fc10, 0x0e72357d, 0xbfeae147, 0xae147ade},	/* 1.37404=f(-0.84)*/
{63, 0,123,__LINE__, 0x3ff5d5be, 0xe7677841, 0xbfea8f5c, 0x28f5c28c},	/* 1.36468=f(-0.83)*/
{63, 0,123,__LINE__, 0x3ff5affc, 0xd9a002ee, 0xbfea3d70, 0xa3d70a3a},	/* 1.35547=f(-0.82)*/
{63, 0,123,__LINE__, 0x3ff58ac8, 0xeda7db18, 0xbfe9eb85, 0x1eb851e8},	/* 1.34638=f(-0.81)*/
{64, 0,123,__LINE__, 0x3ff56622, 0x2fae8258, 0xbfe99999, 0x99999996},	/* 1.33743=f(-0.8)*/
{64, 0,123,__LINE__, 0x3ff54207, 0xaf80b86e, 0xbfe947ae, 0x147ae144},	/* 1.32862=f(-0.79)*/
{64, 0,123,__LINE__, 0x3ff51e78, 0x80825514, 0xbfe8f5c2, 0x8f5c28f2},	/* 1.31994=f(-0.78)*/
{64, 0,123,__LINE__, 0x3ff4fb73, 0xb9a8394f, 0xbfe8a3d7, 0x0a3d70a0},	/* 1.31139=f(-0.77)*/
{64, 0,123,__LINE__, 0x3ff4d8f8, 0x7572582a, 0xbfe851eb, 0x851eb84e},	/* 1.30297=f(-0.76)*/
{63, 0,123,__LINE__, 0x3ff4b705, 0xd1e5d6a6, 0xbfe7ffff, 0xfffffffc},	/* 1.29468=f(-0.75)*/
{64, 0,123,__LINE__, 0x3ff4959a, 0xf08742b7, 0xbfe7ae14, 0x7ae147aa},	/* 1.28652=f(-0.74)*/
{64, 0,123,__LINE__, 0x3ff474b6, 0xf654e136, 0xbfe75c28, 0xf5c28f58},	/* 1.27849=f(-0.73)*/
{64, 0,123,__LINE__, 0x3ff45459, 0x0bc11295, 0xbfe70a3d, 0x70a3d706},	/* 1.27059=f(-0.72)*/
{63, 0,123,__LINE__, 0x3ff43480, 0x5cacce31, 0xbfe6b851, 0xeb851eb4},	/* 1.26282=f(-0.71)*/
{63, 0,123,__LINE__, 0x3ff4152c, 0x1862342e, 0xbfe66666, 0x66666662},	/* 1.25517=f(-0.7)*/
{64, 0,123,__LINE__, 0x3ff3f65b, 0x718f359f, 0xbfe6147a, 0xe147ae10},	/* 1.24765=f(-0.69)*/
{63, 0,123,__LINE__, 0x3ff3d80d, 0x9e4052f3, 0xbfe5c28f, 0x5c28f5be},	/* 1.24025=f(-0.68)*/
{64, 0,123,__LINE__, 0x3ff3ba41, 0xd7db706d, 0xbfe570a3, 0xd70a3d6c},	/* 1.23297=f(-0.67)*/
{63, 0,123,__LINE__, 0x3ff39cf7, 0x5b1ac08f, 0xbfe51eb8, 0x51eb851a},	/* 1.22582=f(-0.66)*/
{64, 0,123,__LINE__, 0x3ff3802d, 0x6807c462, 0xbfe4cccc, 0xccccccc8},	/* 1.21879=f(-0.65)*/
{63, 0,123,__LINE__, 0x3ff363e3, 0x41f6615f, 0xbfe47ae1, 0x47ae1476},	/* 1.21189=f(-0.64)*/
{64, 0,123,__LINE__, 0x3ff34818, 0x2f800cf6, 0xbfe428f5, 0xc28f5c24},	/* 1.2051=f(-0.63)*/
{64, 0,123,__LINE__, 0x3ff32ccb, 0x7a7f0d82, 0xbfe3d70a, 0x3d70a3d2},	/* 1.19844=f(-0.62)*/
{64, 0,123,__LINE__, 0x3ff311fc, 0x7009d086, 0xbfe3851e, 0xb851eb80},	/* 1.19189=f(-0.61)*/
{63, 0,123,__LINE__, 0x3ff2f7aa, 0x606e562f, 0xbfe33333, 0x3333332e},	/* 1.18547=f(-0.6)*/
{64, 0,123,__LINE__, 0x3ff2ddd4, 0x9f2db1db, 0xbfe2e147, 0xae147adc},	/* 1.17916=f(-0.59)*/
{64, 0,123,__LINE__, 0x3ff2c47a, 0x82f79fa1, 0xbfe28f5c, 0x28f5c28a},	/* 1.17297=f(-0.58)*/
{63, 0,123,__LINE__, 0x3ff2ab9b, 0x65a62eb4, 0xbfe23d70, 0xa3d70a38},	/* 1.1669=f(-0.57)*/
{63, 0,123,__LINE__, 0x3ff29336, 0xa439807d, 0xbfe1eb85, 0x1eb851e6},	/* 1.16094=f(-0.56)*/
{64, 0,123,__LINE__, 0x3ff27b4b, 0x9ed39c60, 0xbfe19999, 0x99999994},	/* 1.1551=f(-0.55)*/
{63, 0,123,__LINE__, 0x3ff263d9, 0xb8b45808, 0xbfe147ae, 0x147ae142},	/* 1.14938=f(-0.54)*/
{64, 0,123,__LINE__, 0x3ff24ce0, 0x58355416, 0xbfe0f5c2, 0x8f5c28f0},	/* 1.14377=f(-0.53)*/
{64, 0,123,__LINE__, 0x3ff2365e, 0xe6c60d31, 0xbfe0a3d7, 0x0a3d709e},	/* 1.13827=f(-0.52)*/
{63, 0,123,__LINE__, 0x3ff22054, 0xd0e80141, 0xbfe051eb, 0x851eb84c},	/* 1.13289=f(-0.51)*/
{63, 0,123,__LINE__, 0x3ff20ac1, 0x862ae8cf, 0xbfdfffff, 0xfffffff4},	/* 1.12763=f(-0.5)*/
{64, 0,123,__LINE__, 0x3ff1f5a4, 0x7929046e, 0xbfdf5c28, 0xf5c28f50},	/* 1.12247=f(-0.49)*/
{64, 0,123,__LINE__, 0x3ff1e0fd, 0x1f837e10, 0xbfdeb851, 0xeb851eac},	/* 1.11743=f(-0.48)*/
{64, 0,123,__LINE__, 0x3ff1ccca, 0xf1dede2c, 0xbfde147a, 0xe147ae08},	/* 1.1125=f(-0.47)*/
{64, 0,123,__LINE__, 0x3ff1b90d, 0x6bdf94ad, 0xbfdd70a3, 0xd70a3d64},	/* 1.10768=f(-0.46)*/
{63, 0,123,__LINE__, 0x3ff1a5c4, 0x0c269583, 0xbfdccccc, 0xccccccc0},	/* 1.10297=f(-0.45)*/
{64, 0,123,__LINE__, 0x3ff192ee, 0x544e08c8, 0xbfdc28f5, 0xc28f5c1c},	/* 1.09837=f(-0.44)*/
{64, 0,123,__LINE__, 0x3ff1808b, 0xc8e60e64, 0xbfdb851e, 0xb851eb78},	/* 1.09388=f(-0.43)*/
{64, 0,123,__LINE__, 0x3ff16e9b, 0xf1719512, 0xbfdae147, 0xae147ad4},	/* 1.0895=f(-0.42)*/
{63, 0,123,__LINE__, 0x3ff15d1e, 0x586344c0, 0xbfda3d70, 0xa3d70a30},	/* 1.08523=f(-0.41)*/
{64, 0,123,__LINE__, 0x3ff14c12, 0x8b1a7c2a, 0xbfd99999, 0x9999998c},	/* 1.08107=f(-0.4)*/
{64, 0,123,__LINE__, 0x3ff13b78, 0x19e0619a, 0xbfd8f5c2, 0x8f5c28e8},	/* 1.07702=f(-0.39)*/
{64, 0,123,__LINE__, 0x3ff12b4e, 0x97e506cd, 0xbfd851eb, 0x851eb844},	/* 1.07307=f(-0.38)*/
{64, 0,123,__LINE__, 0x3ff11b95, 0x9b3c9fcd, 0xbfd7ae14, 0x7ae147a0},	/* 1.06923=f(-0.37)*/
{64, 0,123,__LINE__, 0x3ff10c4c, 0xbcdcccca, 0xbfd70a3d, 0x70a3d6fc},	/* 1.0655=f(-0.36)*/
{64, 0,123,__LINE__, 0x3ff0fd73, 0x9899f6d1, 0xbfd66666, 0x66666658},	/* 1.06188=f(-0.35)*/
{64, 0,123,__LINE__, 0x3ff0ef09, 0xcd24bf4b, 0xbfd5c28f, 0x5c28f5b4},	/* 1.05836=f(-0.34)*/
{63, 0,123,__LINE__, 0x3ff0e10e, 0xfc078244, 0xbfd51eb8, 0x51eb8510},	/* 1.05495=f(-0.33)*/
{63, 0,123,__LINE__, 0x3ff0d382, 0xc9a3eb5d, 0xbfd47ae1, 0x47ae146c},	/* 1.05164=f(-0.32)*/
{64, 0,123,__LINE__, 0x3ff0c664, 0xdd309d5c, 0xbfd3d70a, 0x3d70a3c8},	/* 1.04844=f(-0.31)*/
{63, 0,123,__LINE__, 0x3ff0b9b4, 0xe0b6ec4b, 0xbfd33333, 0x33333324},	/* 1.04534=f(-0.3)*/
{64, 0,123,__LINE__, 0x3ff0ad72, 0x8110aa19, 0xbfd28f5c, 0x28f5c280},	/* 1.04235=f(-0.29)*/
{64, 0,123,__LINE__, 0x3ff0a19d, 0x6de605ab, 0xbfd1eb85, 0x1eb851dc},	/* 1.03946=f(-0.28)*/
{64, 0,123,__LINE__, 0x3ff09635, 0x59ab7c50, 0xbfd147ae, 0x147ae138},	/* 1.03667=f(-0.27)*/
{64, 0,123,__LINE__, 0x3ff08b39, 0xf99fdd92, 0xbfd0a3d7, 0x0a3d7094},	/* 1.03399=f(-0.26)*/
{64, 0,123,__LINE__, 0x3ff080ab, 0x05ca6145, 0xbfcfffff, 0xffffffe0},	/* 1.03141=f(-0.25)*/
{64, 0,123,__LINE__, 0x3ff07688, 0x38f8cfde, 0xbfceb851, 0xeb851e98},	/* 1.02894=f(-0.24)*/
{64, 0,123,__LINE__, 0x3ff06cd1, 0x50bdbcf5, 0xbfcd70a3, 0xd70a3d50},	/* 1.02657=f(-0.23)*/
{64, 0,123,__LINE__, 0x3ff06386, 0x0d6ed3ec, 0xbfcc28f5, 0xc28f5c08},	/* 1.0243=f(-0.22)*/
{64, 0,123,__LINE__, 0x3ff05aa6, 0x322336b4, 0xbfcae147, 0xae147ac0},	/* 1.02213=f(-0.21)*/
{64, 0,123,__LINE__, 0x3ff05231, 0x84b1ee9c, 0xbfc99999, 0x99999978},	/* 1.02007=f(-0.2)*/
{63, 0,123,__LINE__, 0x3ff04a27, 0xcdb06f28, 0xbfc851eb, 0x851eb830},	/* 1.0181=f(-0.19)*/
{64, 0,123,__LINE__, 0x3ff04288, 0xd8712ae7, 0xbfc70a3d, 0x70a3d6e8},	/* 1.01624=f(-0.18)*/
{63, 0,123,__LINE__, 0x3ff03b54, 0x73023a33, 0xbfc5c28f, 0x5c28f5a0},	/* 1.01448=f(-0.17)*/
{63, 0,123,__LINE__, 0x3ff0348a, 0x6e2c13df, 0xbfc47ae1, 0x47ae1458},	/* 1.01283=f(-0.16)*/
{64, 0,123,__LINE__, 0x3ff02e2a, 0x9d7057c8, 0xbfc33333, 0x33333310},	/* 1.01127=f(-0.15)*/
{64, 0,123,__LINE__, 0x3ff02834, 0xd708ab3d, 0xbfc1eb85, 0x1eb851c8},	/* 1.00982=f(-0.14)*/
{63, 0,123,__LINE__, 0x3ff022a8, 0xf3e5a733, 0xbfc0a3d7, 0x0a3d7080},	/* 1.00846=f(-0.13)*/
{63, 0,123,__LINE__, 0x3ff01d86, 0xcfadd84b, 0xbfbeb851, 0xeb851e71},	/* 1.00721=f(-0.12)*/
{64, 0,123,__LINE__, 0x3ff018ce, 0x48bcd09e, 0xbfbc28f5, 0xc28f5be2},	/* 1.00606=f(-0.11)*/
{64, 0,123,__LINE__, 0x3ff0147f, 0x40224b38, 0xbfb99999, 0x99999953},	/* 1.005=f(-0.1)*/
{63, 0,123,__LINE__, 0x3ff01099, 0x99a1615f, 0xbfb70a3d, 0x70a3d6c4},	/* 1.00405=f(-0.09)*/
{64, 0,123,__LINE__, 0x3ff00d1d, 0x3bafd17f, 0xbfb47ae1, 0x47ae1435},	/* 1.0032=f(-0.08)*/
{63, 0,123,__LINE__, 0x3ff00a0a, 0x0f7557c7, 0xbfb1eb85, 0x1eb851a6},	/* 1.00245=f(-0.07)*/
{64, 0,123,__LINE__, 0x3ff00760, 0x00cb1875, 0xbfaeb851, 0xeb851e2d},	/* 1.0018=f(-0.06)*/
{63, 0,123,__LINE__, 0x3ff0051e, 0xfe3b1bc3, 0xbfa99999, 0x9999990e},	/* 1.00125=f(-0.05)*/
{64, 0,123,__LINE__, 0x3ff00346, 0xf8ffdb76, 0xbfa47ae1, 0x47ae13ef},	/* 1.0008=f(-0.04)*/
{64, 0,123,__LINE__, 0x3ff001d7, 0xe503e214, 0xbf9eb851, 0xeb851da0},	/* 1.00045=f(-0.03)*/
{64, 0,123,__LINE__, 0x3ff000d1, 0xb8e17bb0, 0xbf947ae1, 0x47ae1362},	/* 1.0002=f(-0.02)*/
{63, 0,123,__LINE__, 0x3ff00034, 0x6de27853, 0xbf847ae1, 0x47ae1249},	/* 1.00005=f(-0.01)*/
{64, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3cd19000, 0x00000000},	/* 1=f(9.74915e-16)*/
{64, 0,123,__LINE__, 0x3ff00034, 0x6de27853, 0x3f847ae1, 0x47ae16ad},	/* 1.00005=f(0.01)*/
{64, 0,123,__LINE__, 0x3ff000d1, 0xb8e17bb0, 0x3f947ae1, 0x47ae1594},	/* 1.0002=f(0.02)*/
{64, 0,123,__LINE__, 0x3ff001d7, 0xe503e214, 0x3f9eb851, 0xeb851fd2},	/* 1.00045=f(0.03)*/
{64, 0,123,__LINE__, 0x3ff00346, 0xf8ffdb76, 0x3fa47ae1, 0x47ae1508},	/* 1.0008=f(0.04)*/
{64, 0,123,__LINE__, 0x3ff0051e, 0xfe3b1bc3, 0x3fa99999, 0x99999a27},	/* 1.00125=f(0.05)*/
{64, 0,123,__LINE__, 0x3ff00760, 0x00cb1876, 0x3faeb851, 0xeb851f46},	/* 1.0018=f(0.06)*/
{64, 0,123,__LINE__, 0x3ff00a0a, 0x0f7557c8, 0x3fb1eb85, 0x1eb85232},	/* 1.00245=f(0.07)*/
{64, 0,123,__LINE__, 0x3ff00d1d, 0x3bafd180, 0x3fb47ae1, 0x47ae14c1},	/* 1.0032=f(0.08)*/
{64, 0,123,__LINE__, 0x3ff01099, 0x99a16160, 0x3fb70a3d, 0x70a3d750},	/* 1.00405=f(0.09)*/
{64, 0,123,__LINE__, 0x3ff0147f, 0x40224b39, 0x3fb99999, 0x999999df},	/* 1.005=f(0.1)*/
{64, 0,123,__LINE__, 0x3ff018ce, 0x48bcd09f, 0x3fbc28f5, 0xc28f5c6e},	/* 1.00606=f(0.11)*/
{64, 0,123,__LINE__, 0x3ff01d86, 0xcfadd84c, 0x3fbeb851, 0xeb851efd},	/* 1.00721=f(0.12)*/
{64, 0,123,__LINE__, 0x3ff022a8, 0xf3e5a734, 0x3fc0a3d7, 0x0a3d70c6},	/* 1.00846=f(0.13)*/
{64, 0,123,__LINE__, 0x3ff02834, 0xd708ab3e, 0x3fc1eb85, 0x1eb8520e},	/* 1.00982=f(0.14)*/
{64, 0,123,__LINE__, 0x3ff02e2a, 0x9d7057ca, 0x3fc33333, 0x33333356},	/* 1.01127=f(0.15)*/
{64, 0,123,__LINE__, 0x3ff0348a, 0x6e2c13e0, 0x3fc47ae1, 0x47ae149e},	/* 1.01283=f(0.16)*/
{64, 0,123,__LINE__, 0x3ff03b54, 0x73023a34, 0x3fc5c28f, 0x5c28f5e6},	/* 1.01448=f(0.17)*/
{64, 0,123,__LINE__, 0x3ff04288, 0xd8712ae9, 0x3fc70a3d, 0x70a3d72e},	/* 1.01624=f(0.18)*/
{64, 0,123,__LINE__, 0x3ff04a27, 0xcdb06f2a, 0x3fc851eb, 0x851eb876},	/* 1.0181=f(0.19)*/
{64, 0,123,__LINE__, 0x3ff05231, 0x84b1ee9e, 0x3fc99999, 0x999999be},	/* 1.02007=f(0.2)*/
{64, 0,123,__LINE__, 0x3ff05aa6, 0x322336b6, 0x3fcae147, 0xae147b06},	/* 1.02213=f(0.21)*/
{64, 0,123,__LINE__, 0x3ff06386, 0x0d6ed3ee, 0x3fcc28f5, 0xc28f5c4e},	/* 1.0243=f(0.22)*/
{64, 0,123,__LINE__, 0x3ff06cd1, 0x50bdbcf7, 0x3fcd70a3, 0xd70a3d96},	/* 1.02657=f(0.23)*/
{64, 0,123,__LINE__, 0x3ff07688, 0x38f8cfe0, 0x3fceb851, 0xeb851ede},	/* 1.02894=f(0.24)*/
{64, 0,123,__LINE__, 0x3ff080ab, 0x05ca6147, 0x3fd00000, 0x00000013},	/* 1.03141=f(0.25)*/
{64, 0,123,__LINE__, 0x3ff08b39, 0xf99fdd94, 0x3fd0a3d7, 0x0a3d70b7},	/* 1.03399=f(0.26)*/
{64, 0,123,__LINE__, 0x3ff09635, 0x59ab7c53, 0x3fd147ae, 0x147ae15b},	/* 1.03667=f(0.27)*/
{64, 0,123,__LINE__, 0x3ff0a19d, 0x6de605ad, 0x3fd1eb85, 0x1eb851ff},	/* 1.03946=f(0.28)*/
{64, 0,123,__LINE__, 0x3ff0ad72, 0x8110aa1c, 0x3fd28f5c, 0x28f5c2a3},	/* 1.04235=f(0.29)*/
{64, 0,123,__LINE__, 0x3ff0b9b4, 0xe0b6ec4e, 0x3fd33333, 0x33333347},	/* 1.04534=f(0.3)*/
{64, 0,123,__LINE__, 0x3ff0c664, 0xdd309d5e, 0x3fd3d70a, 0x3d70a3eb},	/* 1.04844=f(0.31)*/
{63, 0,123,__LINE__, 0x3ff0d382, 0xc9a3eb5f, 0x3fd47ae1, 0x47ae148f},	/* 1.05164=f(0.32)*/
{64, 0,123,__LINE__, 0x3ff0e10e, 0xfc078246, 0x3fd51eb8, 0x51eb8533},	/* 1.05495=f(0.33)*/
{64, 0,123,__LINE__, 0x3ff0ef09, 0xcd24bf4e, 0x3fd5c28f, 0x5c28f5d7},	/* 1.05836=f(0.34)*/
{64, 0,123,__LINE__, 0x3ff0fd73, 0x9899f6d4, 0x3fd66666, 0x6666667b},	/* 1.06188=f(0.35)*/
{64, 0,123,__LINE__, 0x3ff10c4c, 0xbcdcccce, 0x3fd70a3d, 0x70a3d71f},	/* 1.0655=f(0.36)*/
{64, 0,123,__LINE__, 0x3ff11b95, 0x9b3c9fd0, 0x3fd7ae14, 0x7ae147c3},	/* 1.06923=f(0.37)*/
{64, 0,123,__LINE__, 0x3ff12b4e, 0x97e506d0, 0x3fd851eb, 0x851eb867},	/* 1.07307=f(0.38)*/
{64, 0,123,__LINE__, 0x3ff13b78, 0x19e0619e, 0x3fd8f5c2, 0x8f5c290b},	/* 1.07702=f(0.39)*/
{63, 0,123,__LINE__, 0x3ff14c12, 0x8b1a7c2e, 0x3fd99999, 0x999999af},	/* 1.08107=f(0.4)*/
{64, 0,123,__LINE__, 0x3ff15d1e, 0x586344c4, 0x3fda3d70, 0xa3d70a53},	/* 1.08523=f(0.41)*/
{64, 0,123,__LINE__, 0x3ff16e9b, 0xf1719516, 0x3fdae147, 0xae147af7},	/* 1.0895=f(0.42)*/
{64, 0,123,__LINE__, 0x3ff1808b, 0xc8e60e68, 0x3fdb851e, 0xb851eb9b},	/* 1.09388=f(0.43)*/
{64, 0,123,__LINE__, 0x3ff192ee, 0x544e08cc, 0x3fdc28f5, 0xc28f5c3f},	/* 1.09837=f(0.44)*/
{64, 0,123,__LINE__, 0x3ff1a5c4, 0x0c269587, 0x3fdccccc, 0xcccccce3},	/* 1.10297=f(0.45)*/
{64, 0,123,__LINE__, 0x3ff1b90d, 0x6bdf94b1, 0x3fdd70a3, 0xd70a3d87},	/* 1.10768=f(0.46)*/
{64, 0,123,__LINE__, 0x3ff1ccca, 0xf1dede30, 0x3fde147a, 0xe147ae2b},	/* 1.1125=f(0.47)*/
{63, 0,123,__LINE__, 0x3ff1e0fd, 0x1f837e15, 0x3fdeb851, 0xeb851ecf},	/* 1.11743=f(0.48)*/
{63, 0,123,__LINE__, 0x3ff1f5a4, 0x79290473, 0x3fdf5c28, 0xf5c28f73},	/* 1.12247=f(0.49)*/
{64, 0,123,__LINE__, 0x3ff20ac1, 0x862ae8d3, 0x3fe00000, 0x0000000b},	/* 1.12763=f(0.5)*/
{63, 0,123,__LINE__, 0x3ff22054, 0xd0e80145, 0x3fe051eb, 0x851eb85d},	/* 1.13289=f(0.51)*/
{64, 0,123,__LINE__, 0x3ff2365e, 0xe6c60d36, 0x3fe0a3d7, 0x0a3d70af},	/* 1.13827=f(0.52)*/
{63, 0,123,__LINE__, 0x3ff24ce0, 0x5835541b, 0x3fe0f5c2, 0x8f5c2901},	/* 1.14377=f(0.53)*/
{64, 0,123,__LINE__, 0x3ff263d9, 0xb8b4580c, 0x3fe147ae, 0x147ae153},	/* 1.14938=f(0.54)*/
{64, 0,123,__LINE__, 0x3ff27b4b, 0x9ed39c65, 0x3fe19999, 0x999999a5},	/* 1.1551=f(0.55)*/
{64, 0,123,__LINE__, 0x3ff29336, 0xa4398081, 0x3fe1eb85, 0x1eb851f7},	/* 1.16094=f(0.56)*/
{63, 0,123,__LINE__, 0x3ff2ab9b, 0x65a62eb9, 0x3fe23d70, 0xa3d70a49},	/* 1.1669=f(0.57)*/
{64, 0,123,__LINE__, 0x3ff2c47a, 0x82f79fa6, 0x3fe28f5c, 0x28f5c29b},	/* 1.17297=f(0.58)*/
{64, 0,123,__LINE__, 0x3ff2ddd4, 0x9f2db1e0, 0x3fe2e147, 0xae147aed},	/* 1.17916=f(0.59)*/
{64, 0,123,__LINE__, 0x3ff2f7aa, 0x606e5634, 0x3fe33333, 0x3333333f},	/* 1.18547=f(0.6)*/
{64, 0,123,__LINE__, 0x3ff311fc, 0x7009d08c, 0x3fe3851e, 0xb851eb91},	/* 1.19189=f(0.61)*/
{63, 0,123,__LINE__, 0x3ff32ccb, 0x7a7f0d87, 0x3fe3d70a, 0x3d70a3e3},	/* 1.19844=f(0.62)*/
{64, 0,123,__LINE__, 0x3ff34818, 0x2f800cfc, 0x3fe428f5, 0xc28f5c35},	/* 1.2051=f(0.63)*/
{64, 0,123,__LINE__, 0x3ff363e3, 0x41f66164, 0x3fe47ae1, 0x47ae1487},	/* 1.21189=f(0.64)*/
{63, 0,123,__LINE__, 0x3ff3802d, 0x6807c467, 0x3fe4cccc, 0xccccccd9},	/* 1.21879=f(0.65)*/
{64, 0,123,__LINE__, 0x3ff39cf7, 0x5b1ac095, 0x3fe51eb8, 0x51eb852b},	/* 1.22582=f(0.66)*/
{64, 0,123,__LINE__, 0x3ff3ba41, 0xd7db7073, 0x3fe570a3, 0xd70a3d7d},	/* 1.23297=f(0.67)*/
{64, 0,123,__LINE__, 0x3ff3d80d, 0x9e4052fa, 0x3fe5c28f, 0x5c28f5cf},	/* 1.24025=f(0.68)*/
{64, 0,123,__LINE__, 0x3ff3f65b, 0x718f35a5, 0x3fe6147a, 0xe147ae21},	/* 1.24765=f(0.69)*/
{64, 0,123,__LINE__, 0x3ff4152c, 0x18623434, 0x3fe66666, 0x66666673},	/* 1.25517=f(0.7)*/
{63, 0,123,__LINE__, 0x3ff43480, 0x5cacce38, 0x3fe6b851, 0xeb851ec5},	/* 1.26282=f(0.71)*/
{64, 0,123,__LINE__, 0x3ff45459, 0x0bc1129c, 0x3fe70a3d, 0x70a3d717},	/* 1.27059=f(0.72)*/
{64, 0,123,__LINE__, 0x3ff474b6, 0xf654e13d, 0x3fe75c28, 0xf5c28f69},	/* 1.27849=f(0.73)*/
{64, 0,123,__LINE__, 0x3ff4959a, 0xf08742be, 0x3fe7ae14, 0x7ae147bb},	/* 1.28652=f(0.74)*/
{64, 0,123,__LINE__, 0x3ff4b705, 0xd1e5d6ad, 0x3fe80000, 0x0000000d},	/* 1.29468=f(0.75)*/
{64, 0,123,__LINE__, 0x3ff4d8f8, 0x75725831, 0x3fe851eb, 0x851eb85f},	/* 1.30297=f(0.76)*/
{63, 0,123,__LINE__, 0x3ff4fb73, 0xb9a83956, 0x3fe8a3d7, 0x0a3d70b1},	/* 1.31139=f(0.77)*/
{63, 0,123,__LINE__, 0x3ff51e78, 0x8082551b, 0x3fe8f5c2, 0x8f5c2903},	/* 1.31994=f(0.78)*/
{63, 0,123,__LINE__, 0x3ff54207, 0xaf80b876, 0x3fe947ae, 0x147ae155},	/* 1.32862=f(0.79)*/
{63, 0,123,__LINE__, 0x3ff56622, 0x2fae8260, 0x3fe99999, 0x999999a7},	/* 1.33743=f(0.8)*/
{64, 0,123,__LINE__, 0x3ff58ac8, 0xeda7db20, 0x3fe9eb85, 0x1eb851f9},	/* 1.34638=f(0.81)*/
{64, 0,123,__LINE__, 0x3ff5affc, 0xd9a002f6, 0x3fea3d70, 0xa3d70a4b},	/* 1.35547=f(0.82)*/
{64, 0,123,__LINE__, 0x3ff5d5be, 0xe7677848, 0x3fea8f5c, 0x28f5c29d},	/* 1.36468=f(0.83)*/
{64, 0,123,__LINE__, 0x3ff5fc10, 0x0e723584, 0x3feae147, 0xae147aef},	/* 1.37404=f(0.84)*/
{64, 0,123,__LINE__, 0x3ff622f1, 0x49de06d9, 0x3feb3333, 0x33333341},	/* 1.38353=f(0.85)*/
{64, 0,123,__LINE__, 0x3ff64a63, 0x9878f7f2, 0x3feb851e, 0xb851eb93},	/* 1.39316=f(0.86)*/
{63, 0,123,__LINE__, 0x3ff67267, 0xfcc7d9d9, 0x3febd70a, 0x3d70a3e5},	/* 1.40293=f(0.87)*/
{63, 0,123,__LINE__, 0x3ff69aff, 0x7d0ce13d, 0x3fec28f5, 0xc28f5c37},	/* 1.41284=f(0.88)*/
{64, 0,123,__LINE__, 0x3ff6c42b, 0x234e5d2c, 0x3fec7ae1, 0x47ae1489},	/* 1.42289=f(0.89)*/
{63, 0,123,__LINE__, 0x3ff6edeb, 0xfd5d8686, 0x3feccccc, 0xccccccdb},	/* 1.43309=f(0.9)*/
{63, 0,123,__LINE__, 0x3ff71843, 0x1cdd6845, 0x3fed1eb8, 0x51eb852d},	/* 1.44342=f(0.91)*/
{64, 0,123,__LINE__, 0x3ff74331, 0x9749e0ce, 0x3fed70a3, 0xd70a3d7f},	/* 1.4539=f(0.92)*/
{63, 0,123,__LINE__, 0x3ff76eb8, 0x85febc7e, 0x3fedc28f, 0x5c28f5d1},	/* 1.46453=f(0.93)*/
{64, 0,123,__LINE__, 0x3ff79ad9, 0x063ee994, 0x3fee147a, 0xe147ae23},	/* 1.4753=f(0.94)*/
{62, 0,123,__LINE__, 0x3ff7c794, 0x393bc5b1, 0x3fee6666, 0x66666675},	/* 1.48623=f(0.95)*/
{64, 0,123,__LINE__, 0x3ff7f4eb, 0x441c8520, 0x3feeb851, 0xeb851ec7},	/* 1.49729=f(0.96)*/
{62, 0,123,__LINE__, 0x3ff822df, 0x5005b411, 0x3fef0a3d, 0x70a3d719},	/* 1.50851=f(0.97)*/
{63, 0,123,__LINE__, 0x3ff85171, 0x8a20d1f1, 0x3fef5c28, 0xf5c28f6b},	/* 1.51988=f(0.98)*/
{64, 0,123,__LINE__, 0x3ff880a3, 0x23a4072a, 0x3fefae14, 0x7ae147bd},	/* 1.53141=f(0.99)*/
{63, 0,123,__LINE__, 0x3ff8b075, 0x51d9f559, 0x3ff00000, 0x00000007},	/* 1.54308=f(1)*/
{63, 0,123,__LINE__, 0x3ff8e0e9, 0x4e29a254, 0x3ff028f5, 0xc28f5c30},	/* 1.55491=f(1.01)*/
{63, 0,123,__LINE__, 0x3ff91200, 0x561e7e15, 0x3ff051eb, 0x851eb859},	/* 1.56689=f(1.02)*/
{63, 0,123,__LINE__, 0x3ff943bb, 0xab7083cb, 0x3ff07ae1, 0x47ae1482},	/* 1.57904=f(1.03)*/
{64, 0,123,__LINE__, 0x3ff9761c, 0x940c7650, 0x3ff0a3d7, 0x0a3d70ab},	/* 1.59134=f(1.04)*/
{64, 0,123,__LINE__, 0x3ff9a924, 0x5a1c3820, 0x3ff0cccc, 0xccccccd4},	/* 1.60379=f(1.05)*/
{64, 0,123,__LINE__, 0x3ff9dcd4, 0x4c0f3f2a, 0x3ff0f5c2, 0x8f5c28fd},	/* 1.61641=f(1.06)*/
{64, 0,123,__LINE__, 0x3ffa112d, 0xbca3248b, 0x3ff11eb8, 0x51eb8526},	/* 1.62919=f(1.07)*/
{63, 0,123,__LINE__, 0x3ffa4632, 0x02ec5096, 0x3ff147ae, 0x147ae14f},	/* 1.64214=f(1.08)*/
{64, 0,123,__LINE__, 0x3ffa7be2, 0x7a5ec339, 0x3ff170a3, 0xd70a3d78},	/* 1.65525=f(1.09)*/
{62, 0,123,__LINE__, 0x3ffab240, 0x82d6f91a, 0x3ff19999, 0x999999a1},	/* 1.66852=f(1.1)*/
{64, 0,123,__LINE__, 0x3ffae94d, 0x80a2ed8b, 0x3ff1c28f, 0x5c28f5ca},	/* 1.68196=f(1.11)*/
{64, 0,123,__LINE__, 0x3ffb210a, 0xdc8b39a7, 0x3ff1eb85, 0x1eb851f3},	/* 1.69557=f(1.12)*/
{63, 0,123,__LINE__, 0x3ffb597a, 0x03dc50c3, 0x3ff2147a, 0xe147ae1c},	/* 1.70934=f(1.13)*/
{64, 0,123,__LINE__, 0x3ffb929c, 0x686fda7b, 0x3ff23d70, 0xa3d70a45},	/* 1.72329=f(1.14)*/
{63, 0,123,__LINE__, 0x3ffbcc73, 0x80b62a90, 0x3ff26666, 0x6666666e},	/* 1.73741=f(1.15)*/
{62, 0,123,__LINE__, 0x3ffc0700, 0xc7bfd6d7, 0x3ff28f5c, 0x28f5c297},	/* 1.75171=f(1.16)*/
{63, 0,123,__LINE__, 0x3ffc4245, 0xbd476b7f, 0x3ff2b851, 0xeb851ec0},	/* 1.76618=f(1.17)*/
{63, 0,123,__LINE__, 0x3ffc7e43, 0xe5bb3de3, 0x3ff2e147, 0xae147ae9},	/* 1.78083=f(1.18)*/
{62, 0,123,__LINE__, 0x3ffcbafc, 0xca475e2d, 0x3ff30a3d, 0x70a3d712},	/* 1.79565=f(1.19)*/
{62, 0,123,__LINE__, 0x4070bbf2, 0xbc2b69c6, 0xc01921fb, 0x54442d18},	/* 267.747=f(-6.28319)*/
{62, 0,123,__LINE__, 0x404bd4e9, 0xaa3e9cdb, 0xc012d97c, 0x7f3321d2},	/* 55.6634=f(-4.71239)*/
{63, 0,123,__LINE__, 0x40272f14, 0x7fee4000, 0xc00921fb, 0x54442d18},	/* 11.592=f(-3.14159)*/
{63, 0,123,__LINE__, 0x400412cc, 0x2a8d4e9e, 0xbff921fb, 0x54442d18},	/* 2.50918=f(-1.5708)*/
{64, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x00000000, 0x00000000},	/* 1=f(0)*/
{63, 0,123,__LINE__, 0x400412cc, 0x2a8d4e9e, 0x3ff921fb, 0x54442d18},	/* 2.50918=f(1.5708)*/
{63, 0,123,__LINE__, 0x40272f14, 0x7fee4000, 0x400921fb, 0x54442d18},	/* 11.592=f(3.14159)*/
{62, 0,123,__LINE__, 0x404bd4e9, 0xaa3e9cdb, 0x4012d97c, 0x7f3321d2},	/* 55.6634=f(4.71239)*/
{60, 0,123,__LINE__, 0x42937047, 0x0aec28ed, 0xc03e0000, 0x00000000},	/* 5.34324e+12=f(-30)*/
{59, 0,123,__LINE__, 0x426c68ab, 0xda31cdcf, 0xc03c4ccc, 0xcccccccd},	/* 9.76121e+11=f(-28.3)*/
{61, 0,123,__LINE__, 0x4244c263, 0x8e2b5842, 0xc03a9999, 0x9999999a},	/* 1.78321e+11=f(-26.6)*/
{62, 0,123,__LINE__, 0x421e56cf, 0x7144c254, 0xc038e666, 0x66666667},	/* 3.25764e+10=f(-24.9)*/
{60, 0,123,__LINE__, 0x41f62b79, 0x1e77d13f, 0xc0373333, 0x33333334},	/* 5.95116e+09=f(-23.2)*/
{64, 0,123,__LINE__, 0x41d03343, 0x003272a8, 0xc0358000, 0x00000001},	/* 1.08718e+09=f(-21.5)*/
{60, 0,123,__LINE__, 0x41a7ad17, 0x51ce1a16, 0xc033cccc, 0xccccccce},	/* 1.9861e+08=f(-19.8)*/
{64, 0,123,__LINE__, 0x41814d0b, 0xc17d4224, 0xc0321999, 0x9999999b},	/* 3.62827e+07=f(-18.1)*/
{60, 0,123,__LINE__, 0x415948e8, 0xe47eadc4, 0xc0306666, 0x66666668},	/* 6.62826e+06=f(-16.4)*/
{64, 0,123,__LINE__, 0x413279f9, 0xd10e6ddb, 0xc02d6666, 0x6666666a},	/* 1.21087e+06=f(-14.7)*/
{60, 0,123,__LINE__, 0x410b00b5, 0x916b613b, 0xc02a0000, 0x00000004},	/* 221207=f(-13)*/
{64, 0,123,__LINE__, 0x40e3bb5a, 0x336a724a, 0xc0269999, 0x9999999e},	/* 40410.8=f(-11.3)*/
{63, 0,123,__LINE__, 0x40bcd664, 0x0c8f67a9, 0xc0233333, 0x33333338},	/* 7382.39=f(-9.6)*/
{63, 0,123,__LINE__, 0x40951290, 0xbdecc6eb, 0xc01f9999, 0x999999a3},	/* 1348.64=f(-7.9)*/
{63, 0,123,__LINE__, 0x406ecc04, 0x62869202, 0xc018cccc, 0xccccccd6},	/* 246.376=f(-6.2)*/
{62, 0,123,__LINE__, 0x404681ce, 0xb064138b, 0xc0120000, 0x00000009},	/* 45.0141=f(-4.5)*/
{64, 0,123,__LINE__, 0x40208165, 0x9e7a609e, 0xc0066666, 0x66666678},	/* 8.25273=f(-2.8)*/
{63, 0,123,__LINE__, 0x3ffab240, 0x82d6f940, 0xbff19999, 0x999999bd},	/* 1.66852=f(-1.1)*/
{64, 0,123,__LINE__, 0x3ff2f7aa, 0x606e561a, 0x3fe33333, 0x333332ec},	/* 1.18547=f(0.6)*/
{62, 0,123,__LINE__, 0x4014261d, 0x2b7d6154, 0x40026666, 0x66666654},	/* 5.03722=f(2.3)*/
{64, 0,123,__LINE__, 0x403b4ee8, 0x58de3e43, 0x400fffff, 0xffffffee},	/* 27.3082=f(4)*/
{64, 0,123,__LINE__, 0x4062adee, 0x9455e3ef, 0x4016cccc, 0xccccccc4},	/* 149.435=f(5.7)*/
{63, 0,123,__LINE__, 0x40898ff0, 0xaea73115, 0x401d9999, 0x99999991},	/* 817.993=f(7.4)*/
{63, 0,123,__LINE__, 0x40b17da5, 0x7af77ec2, 0x40223333, 0x3333332f},	/* 4477.65=f(9.1)*/
{63, 0,123,__LINE__, 0x40d7ef99, 0xa3138b93, 0x40259999, 0x99999995},	/* 24510.4=f(10.8)*/
{64, 0,123,__LINE__, 0x410060c5, 0x2566b454, 0x4028ffff, 0xfffffffb},	/* 134169=f(12.5)*/
{60, 0,123,__LINE__, 0x412669c0, 0x308d36e7, 0x402c6666, 0x66666661},	/* 734432=f(14.2)*/
{63, 0,123,__LINE__, 0x414eac09, 0x532f3e89, 0x402fcccc, 0xccccccc7},	/* 4.02024e+06=f(15.9)*/
{61, 0,123,__LINE__, 0x4174fcb4, 0x4c4756df, 0x40319999, 0x99999997},	/* 2.20066e+07=f(17.6)*/
{62, 0,123,__LINE__, 0x419cb879, 0xa3e73665, 0x40334ccc, 0xccccccca},	/* 1.20463e+08=f(19.3)*/
{62, 0,123,__LINE__, 0x41c3a6e1, 0xfd9eecc2, 0x4034ffff, 0xfffffffd},	/* 6.59408e+08=f(21)*/
{61, 0,123,__LINE__, 0x41eae4b2, 0x68df16f2, 0x4036b333, 0x33333330},	/* 3.60956e+09=f(22.7)*/
{61, 0,123,__LINE__, 0x421266ce, 0xffa8459a, 0x40386666, 0x66666663},	/* 1.97586e+10=f(24.4)*/
{62, 0,123,__LINE__, 0x42392ead, 0xfa098707, 0x403a1999, 0x99999996},	/* 1.08157e+11=f(26.1)*/
{61, 0,123,__LINE__, 0x42613b19, 0x1e69fb1e, 0x403bcccc, 0xccccccc9},	/* 5.92048e+11=f(27.8)*/
{60, 0,123,__LINE__, 0x42879487, 0x9e85b8ea, 0x403d7fff, 0xfffffffc},	/* 3.24084e+12=f(29.5)*/
{0},
};
void test_cosh(int m)   {run_vector_1(m,cosh_vec,(char *)(cosh),"cosh","dd");   }	
