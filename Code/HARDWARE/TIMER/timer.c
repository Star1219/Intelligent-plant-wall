#include "timer.h"
#include "led.h"
#include "switch.h"
#include "usart.h"


//通用定时器2中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
//最大大约定时50秒

void TIM2_Int_Init(u16 arr2,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM2时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr2; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM2,ENABLE);                    //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//定时器3中断初始化
void TIM3_Int_Init(u16 arr3,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr3; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//通用定时器4中断初始化
void TIM7_Int_Init(u16 arr7,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr7; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM7,ENABLE);                    //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


//通用定时器5中断初始化
void TIM5_Int_Init(u16 arr5,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr5; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM5,ENABLE);                    //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


//定时器2中断服务函数
//程序开机运行后先进入入中断函数，再倒数计时
u8 control0 = OPEN_PUMP;
u8 control4 = OPEN_PUMP;
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
		SWITCH0 = CLOSE;      //关闭状态
		SWITCH4 = CLOSE;
		if ( control4==OPEN_PUMP && control0==GROUPONE_END )
		{
			SWITCH4 = OPEN;
			control4 = TIM_DISABLE;
		}
		if ( control0 == TIM_DISABLE )
		{
			TIM_Cmd (TIM2, DISABLE);
			control0 = GROUPONE_END;
		}
		if ( control0 == OPEN_PUMP )
		{
			SWITCH0 = OPEN;      //只进入一次，为开启状态
			control0 = TIM_DISABLE;
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}


//定时器3中断服务函数
u8 control1 = OPEN_PUMP;
u8 control5 = OPEN_PUMP;
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{ 
		SWITCH5 = CLOSE;
		SWITCH1 = CLOSE;
//		LED1 = !CLOSE;      //led1等于1为点亮led1  led0等于0为点亮led0
		if ( control5==OPEN_PUMP && control1==GROUPONE_END )
		{
			SWITCH5 = OPEN;
			control5 = TIM_DISABLE;
		}
		if ( control1 == TIM_DISABLE )
		{
			TIM_Cmd(TIM3, DISABLE);
			control1 = GROUPONE_END;
		}
		if ( control1 == OPEN_PUMP )
		{
//			LED1 = !OPEN;
			SWITCH1 = OPEN;
			control1 = TIM_DISABLE;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}

//定时器7中断服务函数     //定时器4被usart使用了，用定时器7代替
u8 control2 = OPEN_PUMP;
u8 control6 = OPEN_PUMP;
void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //溢出中断
	{
		LED0 = !CLOSE;
		LED1 = !CLOSE;
		SWITCH2 = CLOSE;      //led1等于1为点亮led1  led0等于0为点亮led0
		SWITCH6 = CLOSE;
		if ( control6==OPEN_PUMP && control2==GROUPONE_END )
		{
			SWITCH6 = OPEN;
			LED1 = !OPEN;
			control6 = TIM_DISABLE;
		}
		if ( control2 == TIM_DISABLE )
		{
			TIM_Cmd(TIM7, DISABLE);
			control2 = GROUPONE_END;
		}
		if ( control2 == OPEN_PUMP )
		{
			LED0 = !OPEN;
			SWITCH2 = OPEN;
			control2 = TIM_DISABLE;
		}
	}
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //清除中断标志位
}


//定时器5中断服务函数
u8 control3 = OPEN_PUMP;
u8 control7 = OPEN_PUMP;
void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
    SWITCH3 = CLOSE;
//		LED0 = !CLOSE;      //led1和led0都是接vcc的，也就是说等于0时为点亮状态
		SWITCH7 = CLOSE;
		if ( control7==OPEN_PUMP && control3==GROUPONE_END )
		{
			SWITCH7 = OPEN;
			control7 = TIM_DISABLE;
		}
		if ( control3 == TIM_DISABLE )
		{
			TIM_Cmd(TIM5, DISABLE);
			control3 = GROUPONE_END;
		}
		if ( control3 == OPEN_PUMP )
		{
//			LED0 = !OPEN;
			SWITCH3 = OPEN;
			control3 = TIM_DISABLE;
		}
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}

