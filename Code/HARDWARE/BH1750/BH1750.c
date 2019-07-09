#include "sys.h"
#include "delay.h"
#include "BH1750.h"
#include "myiic.h"


#define POWER_ON 0X01
#define RESET    0X07
#define MODEH2   0X11
#define	SLAVE_ADDRESS    0x46 //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
                              //ALT  ADDRESS���Žӵ�ʱ��ַΪ0x46���ӵ�Դʱ��ַΪ0xB8

void write_bh1750(u8 REG_Address)
{
  IIC_Start();                  //��ʼ�ź�
  IIC_Send_Byte(SLAVE_ADDRESS);   //�����豸��ַ+д�ź�
	IIC_Wait_Ack();
  IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ��
	IIC_Wait_Ack();
  IIC_Stop();                   //����ֹͣ�ź�
}

u16 read_bh1750(void)
{  
  u16 buf;	
  IIC_Start();                         //��ʼ�ź�
	IIC_Send_Byte(SLAVE_ADDRESS+1);         //���Ϳ�ʼ��������
  IIC_Wait_Ack();  
	
	buf = IIC_Read_Byte(1);
	buf = buf<<8;
  buf += 0x00ff&IIC_Read_Byte(0);
	IIC_Stop();  
  delay_ms(5);
	return buf;
}

void BH1750_Init(void)
{
  write_bh1750(POWER_ON);
	write_bh1750(RESET);
	write_bh1750(MODEH2);
	delay_ms(180);
}


