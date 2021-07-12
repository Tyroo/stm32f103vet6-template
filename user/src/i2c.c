/* 软件IIC模块 */
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
	
	SCL_H, SDA_H;		// 拉高SCL和SDA，准备发送起始信号
	// 延时4us
	SDA_L;					// 在SCL高电平时，拉低SDA，发送起始信号
	// 延时4us
	SCL_L;					// 将SCL拉低，准备发送数据
	
}


// 发送结束信号，SCK高电平下，SDA由低变高
void IIC_Stop() {
	
	I2C_Mode_Tx();	// 设置I2C为发送模式
	
	SCL_L, SDA_L;		// 拉高SCL，拉低SDA
	// 延时4us
	SCL_H, SDA_H;					// 拉高SDA，产生结束信号
	// 延时4us
}


// 不发送应答信号
void IIC_Ack(void){ 
	
	I2C_Mode_Tx();
	
	SCL_L;
	
	SDA_L;
	// 延时2us
	SCL_H;
	// 延时2us
	SCL_L;
}



// 不发送应答信号
void IIC_NotAck(void){ 
	
	I2C_Mode_Tx();
	
	SCL_L;
	
	SDA_H;
	// 延时2us
	SCL_H;
	// 延时2us
	SCL_L;
}


// 发送8位数据
void Send_Data_8Bit(u8 Data) {
	
	IIC_Start();	// 发送数据之前，发送一个起始信号
	
	for(int i=7;i>=0;i--) {
		
		if (Data&(1<<i)) SDA_H;
		else SDA_L;
		
		// 延时2us
		SCL_H;
		// 延时2us
		SCL_L;
		// 延时2us
	}
}
