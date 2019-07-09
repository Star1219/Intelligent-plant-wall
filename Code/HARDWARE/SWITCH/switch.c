#include "switch.h"
#include "sys.h"


void SWITCH_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3|
	                              GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7|
	                              GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出	模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化	
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_2 | GPIO_Pin_3|
	                GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_6 | GPIO_Pin_7
	                 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);
}

