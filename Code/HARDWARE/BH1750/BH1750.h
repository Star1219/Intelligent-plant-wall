#ifndef __BH1750_H
#define __BH1750_H
#include "sys.h"

															
void write_bh1750(u8 REG_Address);
u16 read_bh1750(void);
void BH1750_Init(void);

#endif

