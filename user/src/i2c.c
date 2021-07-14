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
	
	IIC_Mode_Tx();	// 设置I2C为发送模式
	
	IIC_SCL = 1, IIC_SDA_OUT = 1;		// 拉高SCL和SDA，准备发送起始信号
	// 延时4us
	IIC_SDA_OUT = 0;								// 在SCL高电平时，拉低SDA，发送起始信号
	// 延时4us
	IIC_SCL = 0;										// 将SCL拉低，准备发送数据
	
}


// 发送结束信号，SCK高电平下，SDA由低变高
void IIC_Stop() {
	
	IIC_Mode_Tx();	// 设置I2C为发送模式
	
	IIC_SCL = 0, IIC_SDA_OUT = 0;		// 拉高SCL，拉低SDA
	
	Delay_Us(4);
	IIC_SCL = 1, IIC_SDA_OUT = 1;		// 拉高SDA，产生结束信号
	
	Delay_Us(4);
}


// 发送应答信号，发送完数据后发送一个低电平
void IIC_SendAck(void){ 
	
	IIC_Mode_Tx();
	
	IIC_SCL = 0;
	
	IIC_SDA_OUT = 0;
	
	Delay_Us(2);
	IIC_SCL = 1;
	
	Delay_Us(2);
	IIC_SCL = 0;
}


bool IIC_WaitAck(void) {
	
	u8 TimeoutCount = 0;	// 从设备应答超时计数
	
	IIC_Mode_Rx(); 				// SDA设置为输入 
	
	// 将SDA和SCL置为高电平，等待从设备发送SDA为低电平的应答信号
	IIC_SDA_OUT = 1;
	Delay_Us(1);
	
	IIC_SCL=1;
	Delay_Us(1);
	
	// 等待从设备将SDA拉低
	while(IIC_SDA_IN) {
		
		TimeoutCount++;
		
		// 当接受应答等待时间超过250个时钟周期后视为通信失败
		if(TimeoutCount>250) { 
			IIC_Stop();	// 发送通信停止信号给从设备
			return False;
		}
	}
	
	IIC_SCL = 0; //时钟输出 0 
	
	return True; 
} 



// 不发送应答信号，发送完数据后发送一个高电平
void IIC_NotAck(void){ 
	
	IIC_Mode_Tx();
	
	IIC_SCL = 0;
	
	IIC_SDA_OUT = 1;
	
	Delay_Us(2);
	IIC_SCL = 1;
	
	Delay_Us(2);
	IIC_SCL = 0;
}


// 发送8位数据
void IIC_Send_Byte(u8 Data) {
	
	IIC_Mode_Tx();	// 将IIC设置为发送模式
	
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
u8 IIC_Read_Byte(short IsAck) {
	
	static u8 RxData = 0;
	short RxIndex;
	
	IIC_Mode_Rx();
	
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
		IIC_SendAck();
	}
	
	return RxData
}


// 发送一个字符串给从设备
bool IIC_Send_String(u8 *Str, u8 Addr) {
	
	bool WaitSignal;						// 应答标志位
	
	IIC_Start();								// 发送IIC起始信号
	
	WaitSignal = IIC_WaitAck();	// 获取应答信号
	
	if (WaitSignal == False) {	// 当未获取应答信号时终止发送，发送失败
		return False;
	}
	
	IIC_Send_Byte(Addr>>8);				// 发送目标地址高位
	IIC_WaitAck();							// 应答接收
	
	IIC_Send_Byte(Addr%256); 		// 发送低地址
	IIC_WaitAck(); 							// 等待应答
	
	// 当遇到结束字符后停止发送
	while(*Str != '\n')
		IIC_Send_Byte(*Str++);		// 发送一个字符
	
	IIC_Stop();		// 发送IIC结束信号
	
	return True;
}


// 接收一个字符串
u8 IIC_ReadString(u16 Addr, u8 StrLen, u8 StartSignal) {
	
	static u8 RxData[IIC_DATA_SIZE_MAX];
	u8 DataIndex = 0;
	
	if (StrLen>IIC_DATA_SIZE_MAX) return 0;
	
	IIC_Start();										// 发送IIC起始信号
	
	while(DataIndex<StrLen) {
	
		IIC_WaitAck();
		IIC_Send_Byte(Addr%256); 			//发送低地址
		
		IIC_WaitAck(); 
		IIC_Start(); 
		
		IIC_Send_Byte(StartSignal); 	//进入接收模式 
		IIC_WaitAck();
		
		RxData[DataIndex] = IIC_Read_Byte(8);
		
		IIC_Stop();										// 停止发送
		DataIndex++;
	}
}
