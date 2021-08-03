/* SPI通信模块（验证通过） */
#include "spi.h"


u8 SpiReceiveData[50];

// SPI1初始化函数
void Spi1_Init() {
	
	/* 配置结构体定义 */
	SPI_InitTypeDef SPI_InitStructure;																	// 定义SPI配置结构体
	GPIO_InitTypeDef GPIO_InitStructure;																// 定义GPIO配置结构体
	
	/* 时钟使能 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE); 
// 使能SPI1和GPIOA中断
	
	/* 配置GPIO */
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;											// 将IO口设置为复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;										// 设置输出速度为50MHz

	/* 配置SPI1 */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// 设置为2线双向全双工模式
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;												// 设置为主机
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;// 设置SPI传输速率（速率=72MHz/v）
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;										// SPI单次传输的数据量
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;												// 在时钟的第二次跳变沿采集数据
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;													// 设置SPI时钟在低电平时为空闲状态
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;									// 设置数据传输从MSB位开始
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;														// 设置NSS信号由软件控制
	SPI_InitStructure.SPI_CRCPolynomial = 7;														// RCR校验多项式，大于1即可
	
	/* 初始化配置 */
	GPIO_Init(GPIOA, &GPIO_InitStructure);															// 初始化GPIOA5、6、7配置
	SPI_Init(SPI1, &SPI_InitStructure);																	// 初始化SPI1配置
	
	/* 使能/失能 */
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);										// 使能SPI1接受非空中断
	SPI_Cmd(SPI1, ENABLE);																							// 使能SPI1外设
	Nvic_Config(SPI1_IRQn, 1, 1, ENABLE);																// 配置SPI中断优先级
	
}


// 使用SPI1发送数据
bool SPI1_Send(u8* SendData) {
	
	// 在没有遇到结束字符时一直发送
	while(*SendData != '\0') {
		// 等待发送缓冲区清空
		while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
		
		SPI_I2S_SendData(SPI1, *(SendData++));
	}
	return True;
}


// SPI1通信<中断函数>
void SPI1_IRQHandler() {
	
	u8 RxData;							// 定义一个接收每个字节的变量
	static u8 RxIndex = 0;	// 接受数组的索引
	// SPI接收缓冲区非空标志
	FlagStatus ReadFlag = SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE);
	
	// 进入中断后，当接受缓冲区不为空
	if (ReadFlag != RESET) {
		RxData = SPI_I2S_ReceiveData(SPI1);	// 获取接收缓冲区的值
		SpiReceiveData[RxIndex++] = RxData;	// 存入接收数据数组中
		
		// 当遇到换行字符后终止接收
		if (RxData == '\n') {
			RxIndex = 0;
			SpiReceiveData[RxIndex-1] = '\0'; // 将最后位设置为结束字符
			return;
		}
	}
}
