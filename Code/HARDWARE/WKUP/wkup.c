#include "wkup.h"
#include "sys.h"


//////////////////////////////////////////////////////////////////////////////////	 
//ʹ��alarmA��Ϊ����Դ							  
//////////////////////////////////////////////////////////////////////////////////
 
//ϵͳ�������ģʽ
void Sys_Enter_Standby(void)
{
	RCC_AHB1PeriphResetCmd(0X04FF,ENABLE);//��λ����IO��
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//ʹ��PWRʱ��		 
	 
	PWR_BackupAccessCmd(ENABLE);//���������ʹ��
	
	PWR_ClearFlag(PWR_FLAG_WU);//���Wake-up ��־
	
	PWR_EnterSTANDBYMode();	//�������ģʽ
	 
}


















