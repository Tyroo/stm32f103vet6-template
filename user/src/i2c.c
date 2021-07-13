/* 软件IIC模块（未验证） */
#include "i2c.h"


void IIC_Init() {
	
	/* 配置结构体定义 */
	GPIO_InitTypeDef GPIO_InitStructre;											// 定义一个GPIO配置结构体
	
	/* 使能时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		// 使能GPIOB时钟
	
	/* 配置GPIO */
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;					// GPIO推挽输出
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;	// 配置Pin10~11
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;				// 输出速度为50MHz
	
	/* 初始化GPIO */
	GPIO_Init(GPIOB, &GPIO_InitStructre);										// 应用GPIOB配置
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);					// 初始拉高SCK（Pin10）和SDA（Pin11）
}


// 发送起始信号，SCK高电平下，SDA由高变低
void IIC_Start() {
	
	I2C_Mode_Tx();	// 设置I2C为发送模式
	
	IIC_SCL = 1, IIC_SDA_OUT = 1;		// 拉高SCL和SDA，准备发送起始信号
	// 延时4us
	IIC_SDA_OUT = 0;					// 在SCL高电平时，拉低SDA，发送起始信号
	// 延时4us
	IIC_SCL = 0;					// 将SCL拉低，准备发送数据
	
}


// 发送结束信号，SCK高电平下，SDA由低变高
void IIC_Stop() {
	
	I2C_Mode_Tx();	// 设置I2C为发送模式
	
	IIC_SCL = 0, IIC_SDA_OUT = 0;		// 拉高SCL，拉低SDA
	
	Delay_Us(4);
	IIC_SCL = 1, IIC_SDA_OUT = 1;					// 拉高SDA，产生结束信号
	
	Delay_Us(4);
}


// 不发送应答信号
void IIC_Ack(void){ 
	
	I2C_Mode_Tx();
	
	IIC_SCL = 0;
	
	IIC_SDA_OUT = 0;
	
	Delay_Us(2);
	IIC_SCL = 1;
	
	Delay_Us(2);
	IIC_SCL = 0;
}



// 不发送应答信号
void IIC_NotAck(void){ 
	
	I2C_Mode_Tx();
	
	IIC_SCL = 0;
	
	IIC_SDA_OUT = 1;
	
	Delay_Us(2);
	IIC_SCL = 1;
	
	Delay_Us(2);
	IIC_SCL = 0;
}


// 发送8位数据
void Send_Data_Byte(u8 Data) {
	
	I2C_Mode_Tx();	// 将IIC设置为发送模式
	
	IIC_SCL = 0;		// 拉低SCL电平，准备发送第一帧数据
	
	for(int i=7;i>=0;i--) {
		
		if (Data&(1<<i)) IIC_SDA_OUT = 1;
		else IIC_SDA_OUT = 0;
		
		Delay_Us(2);
		IIC_SCL = 1;
		
		Delay_Us(2);
		IIC_SCL = 0;
		
		Delay_Us(2);
	}
}


// 接收8位数据
void Read_Data_Byte(short IsAck) {
	
	static unsigned char RxData = 0;
	short RxIndex;
	
	I2C_Mode_Rx();
	
	for (RxIndex=0;RxIndex<8;RxIndex++) {
		
		IIC_SCL = 0;
		
		Delay_Us(2);
		IIC_SCL = 1;
		
		RxData <<= 1;
		if (IIC_SDA_IN) RxData |= 0x01;
	}
	
	if(!IsAck) {
		IIC_NotAck();
	} else {
		IIC_Ack();
	}
}
