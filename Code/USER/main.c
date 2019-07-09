#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "lcd.h"
#include "rtc.h"
#include "wkup.h"
#include "adc.h"
#include "myiic.h"
#include "bh1750.h"
#include "timer.h"
#include "switch.h"
#include "rs485.h"


//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	

//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��ledʱ��
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��iicʱ��
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM2375ʱ��
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ�ӿ���ʱ��

#define DRY_TO_WET 1096.0
#define ENTER_STANDBY_HOURS 19
#define ENTER_STANDBY_MINUTES 33
#define SET_ALARMA_WEEKS 3              //�Ѷ������������룬��ÿ����
#define SET_ALARMA_HOURS 19
#define SET_ALARMA_MINUTES 35
#define SET_ALARMA_SEC 1
#define V_WATER 230      
#define SUIT_WET 3000
#define SUIT_LIGHT 50
#define EIGHT 8

//     2       3     7(4)     5      ��ʱ��
//    / \     / \     / \    / \
//   0   4   1   5   2   6  3   7    ����-

//8��ʪ�ȴ�������Ӧpa0134567��pc01�ֱ���ͨ��0 1 10 11 3 4 5 6 7 
//����01234567��Ӧpc 11 12 1 2 3 4 5 6 7
int main(void)
{ 
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;

	u8 i=0,
	   groupone=1,
	   grouptwo=1,
	   tbuf[40];
	u8 key;
	u32 lux;//��Ź���ǿ����
//  u8 luxfloat;//С������
	u8 luxint;//��������
	u8 l=0;
	u8 rs485buf[9]; 
	u8 command[3]={0xA5,0X09,0XAE};
	float precent[EIGHT],
		    need_water[EIGHT], 
	      time[EIGHT],  
	      arr[EIGHT];
	u16 psc = 65534,
			int_arr[EIGHT],
      wet_adc1_channel[EIGHT];

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	delay_init(168);      //��ʼ����ʱ����
	uart_init(9600);		//��ʼ�����ڲ�����Ϊ115200	
	LED_Init();					  //��ʼ��LED
 	LCD_Init();					  //��ʼ��LCD
	My_RTC_Init();		 		//��ʼ��RTC
	ADC1_Init();          //��ʼ��ADC
	BH1750_Init();
	IIC_Init();	
	SWITCH_Init();
	RS485_Init(9600);		//��ʼ��RS485����2
	RTC_Set_AlarmA(SET_ALARMA_WEEKS, SET_ALARMA_HOURS, SET_ALARMA_MINUTES, SET_ALARMA_SEC);     //���ڣ�Сʱ�����ӣ���
	
	POINT_COLOR=RED;	
	LCD_ShowString(30,50,200,16,16,"RTC TEST");	
	LCD_ShowString(30,130,200,16,16,"ADC TEST");
	LCD_ShowString(30,310,200,16,16,"XLS TEST");


	POINT_COLOR=BLUE; 	
	//����x,y  ���  �߶�  ��С
	LCD_ShowString(30,150,200,16,16,"ADC1_CH0_VAL:");	
	LCD_ShowString(30,170,200,16,16,"ADC1_CH1_VAL:");
	LCD_ShowString(30,190,200,16,16,"ADC1_CH2_VAL:");LCD_ShowString(180,190,200,16,16,"LED0");	
	LCD_ShowString(30,210,200,16,16,"ADC1_CH3_VAL:");
	LCD_ShowString(30,230,200,16,16,"ADC1_CH4_VAL:");	
	LCD_ShowString(30,250,200,16,16,"ADC1_CH5_VAL:");
	LCD_ShowString(30,270,200,16,16,"ADC1_CH6_VAL:");LCD_ShowString(180,270,200,16,16,"LED1");
	LCD_ShowString(30,290,200,16,16,"ADC1_CH7_VAL:");
	LCD_ShowString(30,330,200,16,16,"light_xls:");

	
////***********************************************************************	
////*********************����ʪ�Ȳɼ�����ʾ*******************************
////**********************************************************************
	wet_adc1_channel[0]=Get_Adc_Average(ADC_Channel_0,20);//��ȡͨ��0��ת��ֵ��20��ȡƽ��
	wet_adc1_channel[1]=Get_Adc_Average(ADC_Channel_10,20);//��ȡͨ��1��ת��ֵ��20��ȡƽ��   pa2��pa3��Ϊ���ڣ���pc0��pc3ȡ��֮
  wet_adc1_channel[2]=Get_Adc_Average(ADC_Channel_11,20);//��ȡͨ��2��ת��ֵ��20��ȡƽ��
  wet_adc1_channel[3]=Get_Adc_Average(ADC_Channel_3,20);//��ȡͨ��3��ת��ֵ��20��ȡƽ��
	wet_adc1_channel[4]=Get_Adc_Average(ADC_Channel_4,20);//��ȡͨ��4��ת��ֵ��20��ȡƽ��
	wet_adc1_channel[5]=Get_Adc_Average(ADC_Channel_5,20);//��ȡͨ��5��ת��ֵ��20��ȡƽ��
	wet_adc1_channel[6]=Get_Adc_Average(ADC_Channel_6,20);//��ȡͨ��6��ת��ֵ��20��ȡƽ��
	wet_adc1_channel[7]=Get_Adc_Average(ADC_Channel_7,20);//��ȡͨ��7��ת��ֵ��20��ȡƽ��
	LCD_ShowxNum(134,150,wet_adc1_channel[0],4,16,0);    //��ʾADCC�������ԭʼֵ
	LCD_ShowxNum(134,170,wet_adc1_channel[1],4,16,0);    //��ʾADCC�������ԭʼֵ
	LCD_ShowxNum(134,190,wet_adc1_channel[2],4,16,0);    //��ʾADCC�������ԭʼֵ
	LCD_ShowxNum(134,210,wet_adc1_channel[3],4,16,0);    //��ʾADCC�������ԭʼֵ
	LCD_ShowxNum(134,230,wet_adc1_channel[4],4,16,0);    //��ʾADCC�������ԭʼֵ
	LCD_ShowxNum(134,250,wet_adc1_channel[5],4,16,0);    //��ʾADCC�������ԭʼֵ
	LCD_ShowxNum(134,270,wet_adc1_channel[6],4,16,0);    //��ʾADCC�������ԭʼֵ
	LCD_ShowxNum(134,290,wet_adc1_channel[7],4,16,0);    //��ʾADCC�������ԭʼֵ
	  //����x,y  ��ʾ������  ����  ��С  MODE
//	GROUPONE_SWITCH = OPEN;   //��������
//	GROUPTWO_SWITCH = OPEN;
  BIGBENG_SWITCH = 1;
	delay_ms(500);
			
  while(1) 
	{	

//*****************************************************		
//*******************RTCʱ��ʱ���ȡ����ʾ**************
//*******************************************************	
	  RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);			
		sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
		LCD_ShowString(30,70,210,16,16,tbuf);	
		
		RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);			
		sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 
		LCD_ShowString(30,90,210,16,16,tbuf);	
			
		sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.RTC_WeekDay); 
		LCD_ShowString(30,110,210,16,16,tbuf);
		
//***********************************************************
//*****************����ʪ�Ȳɼ��Ͷ�ʱ�����ؿ���**************
//***********************************************************	
		for (i=0; i<8; i++)
	  {
			if ( (i==0)|(i==1)&&( wet_adc1_channel[i] <= SUIT_WET ) )
			{
				wet_adc1_channel[i] = 3001;
				i += 10;
			  PCout(i) = CLOSE;
			}
			else if( wet_adc1_channel[i] <= SUIT_WET )
			{
				wet_adc1_channel[i] = 3001;
			  PCout(i) = CLOSE;
			}
		}		
	  if(groupone)
		{
			//ͨ�����ADC�ɼ�
			precent[0] = (wet_adc1_channel[0]-SUIT_WET) / DRY_TO_WET ;           //4096��ҪдΪ�����͵�
     	need_water[0] = V_WATER * precent[0]; 	
    	time[0] = need_water[0] / 4.6f ;                                 //4.6����ÿ�� 
      arr[0] = time[0]*84000000 / (65535-1);	
      int_arr[0] = arr[0];                                             //ֻȡ��������
      TIM2_Int_Init (int_arr[0],psc);                              //��ʱ��ʱ��Ƶ��Ϊ84M
			
			//ͨ��һ��ADC�ɼ�
			precent[1] = (wet_adc1_channel[1]-SUIT_WET) / DRY_TO_WET ;        
     	need_water[1] = V_WATER * precent[1]; 	
    	time[1] = need_water[1] / 4.6f ;                                 
      arr[1] = time[1]*84000000 / (65535-1);	
      int_arr[1] = arr[1];                                             
      TIM3_Int_Init (int_arr[1],psc);     //��ʱ��ʱ��Ƶ��Ϊ84M
			
			//ͨ������ADC�ɼ�*************************************************
			precent[2] = (wet_adc1_channel[2]-SUIT_WET) / DRY_TO_WET ;          
     	need_water[2] = V_WATER * precent[2]; 	
    	time[2] = need_water[2] / 4.6f ;                                  
      arr[2] = time[2]*84000000 / (65535-1);	
      int_arr[2] = arr[2];                                            
      TIM7_Int_Init (int_arr[2],psc);     

			//ͨ������ADC�ɼ�*************************************************************
		  precent[3] = (wet_adc1_channel[3]-SUIT_WET) / DRY_TO_WET ;     
     	need_water[3] = V_WATER * precent[3]; 			             
    	time[3] = need_water[3] / 4.6f ;                                                       
      arr[3] = time[3]*84000000 / (65535-1);	
      int_arr[3] = arr[3];                                        
      TIM5_Int_Init (int_arr[3],psc);   			
			
			groupone = 0;
		}	
		
		//��ʱ���ڶ��θ�ֵ��������һ��ˮ�õĿ���
    if ( (RTC_TimeStruct.RTC_Hours == SET_ALARMA_HOURS) && (RTC_TimeStruct.RTC_Minutes == SET_ALARMA_MINUTES+1) )	
		{
			if ( grouptwo )
			{			
			//ͨ���ĵ�ADC�ɼ�***************************************************************
			precent[4] = (wet_adc1_channel[4]-SUIT_WET) / DRY_TO_WET ;          
     	need_water[4] = V_WATER * precent[4]; 	
    	time[4] = need_water[4] / 4.6f ;                                 
      arr[4] = time[4]*84000000 / (65535-1);	
      int_arr[4] = arr[4];                                            			
      TIM2_Int_Init (int_arr[4],psc);     
			
			//ͨ�����ADC�ɼ�***************************************************************
			precent[5] = (wet_adc1_channel[5]-SUIT_WET) / DRY_TO_WET ;          
     	need_water[5] = V_WATER * precent[5]; 	
    	time[5] = need_water[5] / 4.6f ;                                  
      arr[5] = time[5]*84000000 / (65535-1);	
      int_arr[5] = arr[5];                                             
      TIM3_Int_Init (int_arr[5],psc);     


			//ͨ������ADC�ɼ�
			precent[6] = (wet_adc1_channel[6]-SUIT_WET) / DRY_TO_WET ;          
     	need_water[6] = V_WATER * precent[6]; 	        //����������
    	time[6] = need_water[6] / 4.6f ;                                
      arr[6] = time[6]*84000000 / (65535-1);	
      int_arr[6] = arr[6];                                             
      TIM7_Int_Init (int_arr[6],psc);     

			//ͨ���ߵ�ADC�ɼ�
			precent[7] = (wet_adc1_channel[7]-SUIT_WET) / DRY_TO_WET ;         
     	need_water[7] = V_WATER * precent[7]; 	
    	time[7] = need_water[7] / 4.6f ;                                 
      arr[7] = time[7]*84000000 / (65535-1);	
      int_arr[7] = arr[7];                                            
      TIM5_Int_Init (int_arr[7],psc);
      grouptwo = 0;
	  	}			
		}	
		if ( (RTC_TimeStruct.RTC_Hours == SET_ALARMA_HOURS) && (RTC_TimeStruct.RTC_Minutes == SET_ALARMA_MINUTES+2) )
		{
//			GROUPONE_SWITCH = CLOSE ;   
//			GROUPTWO_SWITCH = CLOSE ;
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, DISABLE);//ʹ��GPIOFʱ��ledʱ��
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 |
			                       RCC_APB1Periph_TIM7 | RCC_APB1Periph_TIM5, DISABLE);  ///ʹ��TIM2375ʱ��
 			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, DISABLE);//ʹ��GPIOCʱ�ӿ���ʱ��
		}
		
//**********************************************************************
//*******************���նȲɼ�����ʾ********************************
//*********************************************************************
		for(l=0;l<3;l++)
		{
			rs485buf[l]=command[l];//��䷢�ͻ�����
		}
		RS485_Send_Data(rs485buf,3);//����3���ֽ� 
		delay_ms(500);			
		RS485_Receive_Data(rs485buf,&key);
		lux=(rs485buf[5]<<16)+rs485buf[6]*256+rs485buf[7];
//		luxfloat=lux%100;
    luxint=lux/100;  
		LCD_ShowxNum(110,330,luxint,4,16,0);    //��ʾ���ն�
//		switch (luxint)
//		{
//			case 0: LED_SWITCH = CLOSE; break;
//			case 1:
//			case 100: LED_SWITCH = OPEN;break;
//			default: LED_SWITCH = CLOSE; 
//		}

		
		if ( (RTC_TimeStruct.RTC_Hours == ENTER_STANDBY_HOURS) && (RTC_TimeStruct.RTC_Minutes == ENTER_STANDBY_MINUTES) )
		{
			Sys_Enter_Standby();
		}
	}	
}

