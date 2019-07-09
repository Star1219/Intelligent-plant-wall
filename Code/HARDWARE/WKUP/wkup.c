#include "wkup.h"
#include "sys.h"


//////////////////////////////////////////////////////////////////////////////////	 
//使用alarmA作为唤醒源							  
//////////////////////////////////////////////////////////////////////////////////
 
//系统进入待机模式
void Sys_Enter_Standby(void)
{
	RCC_AHB1PeriphResetCmd(0X04FF,ENABLE);//复位所有IO口
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//使能PWR时钟		 
	 
	PWR_BackupAccessCmd(ENABLE);//后备区域访问使能
	
	PWR_ClearFlag(PWR_FLAG_WU);//清除Wake-up 标志
	
	PWR_EnterSTANDBYMode();	//进入待机模式
	 
}


















