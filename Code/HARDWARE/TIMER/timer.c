#include "timer.h"
#include "led.h"
#include "switch.h"
#include "usart.h"


//ͨ�ö�ʱ��2�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
//����Լ��ʱ50��

void TIM2_Int_Init(u16 arr2,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM2ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr2; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM2,ENABLE);                    //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//��ʱ��3�жϳ�ʼ��
void TIM3_Int_Init(u16 arr3,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr3; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//ͨ�ö�ʱ��4�жϳ�ʼ��
void TIM7_Int_Init(u16 arr7,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr7; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM7,ENABLE);                    //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


//ͨ�ö�ʱ��5�жϳ�ʼ��
void TIM5_Int_Init(u16 arr5,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr5; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM5,ENABLE);                    //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


//��ʱ��2�жϷ�����
//���򿪻����к��Ƚ������жϺ������ٵ�����ʱ
u8 control0 = OPEN_PUMP;
u8 control4 = OPEN_PUMP;
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		SWITCH0 = CLOSE;      //�ر�״̬
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
			SWITCH0 = OPEN;      //ֻ����һ�Σ�Ϊ����״̬
			control0 = TIM_DISABLE;
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
}


//��ʱ��3�жϷ�����
u8 control1 = OPEN_PUMP;
u8 control5 = OPEN_PUMP;
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{ 
		SWITCH5 = CLOSE;
		SWITCH1 = CLOSE;
//		LED1 = !CLOSE;      //led1����1Ϊ����led1  led0����0Ϊ����led0
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
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}

//��ʱ��7�жϷ�����     //��ʱ��4��usartʹ���ˣ��ö�ʱ��7����
u8 control2 = OPEN_PUMP;
u8 control6 = OPEN_PUMP;
void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //����ж�
	{
		LED0 = !CLOSE;
		LED1 = !CLOSE;
		SWITCH2 = CLOSE;      //led1����1Ϊ����led1  led0����0Ϊ����led0
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
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //����жϱ�־λ
}


//��ʱ��5�жϷ�����
u8 control3 = OPEN_PUMP;
u8 control7 = OPEN_PUMP;
void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
    SWITCH3 = CLOSE;
//		LED0 = !CLOSE;      //led1��led0���ǽ�vcc�ģ�Ҳ����˵����0ʱΪ����״̬
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
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
}

