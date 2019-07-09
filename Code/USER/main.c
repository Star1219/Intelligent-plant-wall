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


//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	

//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟led时钟
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟iic时钟
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM2375时钟
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟开关时钟

#define DRY_TO_WET 1096.0
#define ENTER_STANDBY_HOURS 19
#define ENTER_STANDBY_MINUTES 33
#define SET_ALARMA_WEEKS 3              //已对星期设置掩码，即每天闹
#define SET_ALARMA_HOURS 19
#define SET_ALARMA_MINUTES 35
#define SET_ALARMA_SEC 1
#define V_WATER 230      
#define SUIT_WET 3000
#define SUIT_LIGHT 50
#define EIGHT 8

//     2       3     7(4)     5      定时器
//    / \     / \     / \    / \
//   0   4   1   5   2   6  3   7    开关-

//8个湿度传感器对应pa0134567和pc01分别是通道0 1 10 11 3 4 5 6 7 
//开关01234567对应pc 11 12 1 2 3 4 5 6 7
int main(void)
{ 
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;

	u8 i=0,
	   groupone=1,
	   grouptwo=1,
	   tbuf[40];
	u8 key;
	u32 lux;//存放光照强度数
//  u8 luxfloat;//小数部分
	u8 luxint;//整数部分
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

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	delay_init(168);      //初始化延时函数
	uart_init(9600);		//初始化串口波特率为115200	
	LED_Init();					  //初始化LED
 	LCD_Init();					  //初始化LCD
	My_RTC_Init();		 		//初始化RTC
	ADC1_Init();          //初始化ADC
	BH1750_Init();
	IIC_Init();	
	SWITCH_Init();
	RS485_Init(9600);		//初始化RS485串口2
	RTC_Set_AlarmA(SET_ALARMA_WEEKS, SET_ALARMA_HOURS, SET_ALARMA_MINUTES, SET_ALARMA_SEC);     //星期，小时，分钟，秒
	
	POINT_COLOR=RED;	
	LCD_ShowString(30,50,200,16,16,"RTC TEST");	
	LCD_ShowString(30,130,200,16,16,"ADC TEST");
	LCD_ShowString(30,310,200,16,16,"XLS TEST");


	POINT_COLOR=BLUE; 	
	//坐标x,y  宽度  高度  大小
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
////*********************土壤湿度采集和显示*******************************
////**********************************************************************
	wet_adc1_channel[0]=Get_Adc_Average(ADC_Channel_0,20);//获取通道0的转换值，20次取平均
	wet_adc1_channel[1]=Get_Adc_Average(ADC_Channel_10,20);//获取通道1的转换值，20次取平均   pa2和pa3作为串口，由pc0和pc3取代之
  wet_adc1_channel[2]=Get_Adc_Average(ADC_Channel_11,20);//获取通道2的转换值，20次取平均
  wet_adc1_channel[3]=Get_Adc_Average(ADC_Channel_3,20);//获取通道3的转换值，20次取平均
	wet_adc1_channel[4]=Get_Adc_Average(ADC_Channel_4,20);//获取通道4的转换值，20次取平均
	wet_adc1_channel[5]=Get_Adc_Average(ADC_Channel_5,20);//获取通道5的转换值，20次取平均
	wet_adc1_channel[6]=Get_Adc_Average(ADC_Channel_6,20);//获取通道6的转换值，20次取平均
	wet_adc1_channel[7]=Get_Adc_Average(ADC_Channel_7,20);//获取通道7的转换值，20次取平均
	LCD_ShowxNum(134,150,wet_adc1_channel[0],4,16,0);    //显示ADCC采样后的原始值
	LCD_ShowxNum(134,170,wet_adc1_channel[1],4,16,0);    //显示ADCC采样后的原始值
	LCD_ShowxNum(134,190,wet_adc1_channel[2],4,16,0);    //显示ADCC采样后的原始值
	LCD_ShowxNum(134,210,wet_adc1_channel[3],4,16,0);    //显示ADCC采样后的原始值
	LCD_ShowxNum(134,230,wet_adc1_channel[4],4,16,0);    //显示ADCC采样后的原始值
	LCD_ShowxNum(134,250,wet_adc1_channel[5],4,16,0);    //显示ADCC采样后的原始值
	LCD_ShowxNum(134,270,wet_adc1_channel[6],4,16,0);    //显示ADCC采样后的原始值
	LCD_ShowxNum(134,290,wet_adc1_channel[7],4,16,0);    //显示ADCC采样后的原始值
	  //坐标x,y  显示的数字  长度  大小  MODE
//	GROUPONE_SWITCH = OPEN;   //触电吸合
//	GROUPTWO_SWITCH = OPEN;
  BIGBENG_SWITCH = 1;
	delay_ms(500);
			
  while(1) 
	{	

//*****************************************************		
//*******************RTC时钟时间获取和显示**************
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
//*****************土壤湿度采集和定时器开关控制**************
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
			//通道零的ADC采集
			precent[0] = (wet_adc1_channel[0]-SUIT_WET) / DRY_TO_WET ;           //4096需要写为浮点型的
     	need_water[0] = V_WATER * precent[0]; 	
    	time[0] = need_water[0] / 4.6f ;                                 //4.6毫升每秒 
      arr[0] = time[0]*84000000 / (65535-1);	
      int_arr[0] = arr[0];                                             //只取整数部分
      TIM2_Int_Init (int_arr[0],psc);                              //定时器时钟频率为84M
			
			//通道一的ADC采集
			precent[1] = (wet_adc1_channel[1]-SUIT_WET) / DRY_TO_WET ;        
     	need_water[1] = V_WATER * precent[1]; 	
    	time[1] = need_water[1] / 4.6f ;                                 
      arr[1] = time[1]*84000000 / (65535-1);	
      int_arr[1] = arr[1];                                             
      TIM3_Int_Init (int_arr[1],psc);     //定时器时钟频率为84M
			
			//通道二的ADC采集*************************************************
			precent[2] = (wet_adc1_channel[2]-SUIT_WET) / DRY_TO_WET ;          
     	need_water[2] = V_WATER * precent[2]; 	
    	time[2] = need_water[2] / 4.6f ;                                  
      arr[2] = time[2]*84000000 / (65535-1);	
      int_arr[2] = arr[2];                                            
      TIM7_Int_Init (int_arr[2],psc);     

			//通道三的ADC采集*************************************************************
		  precent[3] = (wet_adc1_channel[3]-SUIT_WET) / DRY_TO_WET ;     
     	need_water[3] = V_WATER * precent[3]; 			             
    	time[3] = need_water[3] / 4.6f ;                                                       
      arr[3] = time[3]*84000000 / (65535-1);	
      int_arr[3] = arr[3];                                        
      TIM5_Int_Init (int_arr[3],psc);   			
			
			groupone = 0;
		}	
		
		//定时器第二次赋值，控制下一组水泵的开启
    if ( (RTC_TimeStruct.RTC_Hours == SET_ALARMA_HOURS) && (RTC_TimeStruct.RTC_Minutes == SET_ALARMA_MINUTES+1) )	
		{
			if ( grouptwo )
			{			
			//通道四的ADC采集***************************************************************
			precent[4] = (wet_adc1_channel[4]-SUIT_WET) / DRY_TO_WET ;          
     	need_water[4] = V_WATER * precent[4]; 	
    	time[4] = need_water[4] / 4.6f ;                                 
      arr[4] = time[4]*84000000 / (65535-1);	
      int_arr[4] = arr[4];                                            			
      TIM2_Int_Init (int_arr[4],psc);     
			
			//通道五的ADC采集***************************************************************
			precent[5] = (wet_adc1_channel[5]-SUIT_WET) / DRY_TO_WET ;          
     	need_water[5] = V_WATER * precent[5]; 	
    	time[5] = need_water[5] / 4.6f ;                                  
      arr[5] = time[5]*84000000 / (65535-1);	
      int_arr[5] = arr[5];                                             
      TIM3_Int_Init (int_arr[5],psc);     


			//通道六的ADC采集
			precent[6] = (wet_adc1_channel[6]-SUIT_WET) / DRY_TO_WET ;          
     	need_water[6] = V_WATER * precent[6]; 	        //是六不是三
    	time[6] = need_water[6] / 4.6f ;                                
      arr[6] = time[6]*84000000 / (65535-1);	
      int_arr[6] = arr[6];                                             
      TIM7_Int_Init (int_arr[6],psc);     

			//通道七的ADC采集
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
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, DISABLE);//使能GPIOF时钟led时钟
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 |
			                       RCC_APB1Periph_TIM7 | RCC_APB1Periph_TIM5, DISABLE);  ///使能TIM2375时钟
 			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, DISABLE);//使能GPIOC时钟开关时钟
		}
		
//**********************************************************************
//*******************光照度采集和显示********************************
//*********************************************************************
		for(l=0;l<3;l++)
		{
			rs485buf[l]=command[l];//填充发送缓冲区
		}
		RS485_Send_Data(rs485buf,3);//发送3个字节 
		delay_ms(500);			
		RS485_Receive_Data(rs485buf,&key);
		lux=(rs485buf[5]<<16)+rs485buf[6]*256+rs485buf[7];
//		luxfloat=lux%100;
    luxint=lux/100;  
		LCD_ShowxNum(110,330,luxint,4,16,0);    //显示光照度
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

