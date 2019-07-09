#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
	
void TIM2_Int_Init(u16 arr2,u16 psc);
void TIM3_Int_Init(u16 arr3,u16 psc);
void TIM7_Int_Init(u16 arr7,u16 psc);
void TIM5_Int_Init(u16 arr5,u16 psc);

#define OPEN_PUMP 1
#define TIM_DISABLE 2
#define GROUPONE_END 3
#define OPEN 1
#define CLOSE 0

#endif
