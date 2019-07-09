#include "sys.h"
#include "delay.h"
#include "BH1750.h"
#include "myiic.h"


#define POWER_ON 0X01
#define RESET    0X07
#define MODEH2   0X11
#define	SLAVE_ADDRESS    0x46 //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0x46，接电源时地址为0xB8

void write_bh1750(u8 REG_Address)
{
  IIC_Start();                  //起始信号
  IIC_Send_Byte(SLAVE_ADDRESS);   //发送设备地址+写信号
	IIC_Wait_Ack();
  IIC_Send_Byte(REG_Address);    //内部寄存器地址，
	IIC_Wait_Ack();
  IIC_Stop();                   //发送停止信号
}

u16 read_bh1750(void)
{  
  u16 buf;	
  IIC_Start();                         //起始信号
	IIC_Send_Byte(SLAVE_ADDRESS+1);         //发送开始测量命令
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


