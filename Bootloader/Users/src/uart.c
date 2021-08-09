/** USART收发数据模块（验证通过） **/
#include <string.h>
#include "uart.h"
#include "nvic.h"


// USART1接收的数据
u16 UsartReceiveDataOne[100];
u16 UsartReceiveDataTwo[100];

// 是否处在下载标志
u8 IsDownload = 0;

// 初始化UART
void Uart1_Init(int Baud) {
	
	/* 配置结构体指针定义 */
	USART_InitTypeDef USART_InitStructre;														// 定义一个USART配置结构体
	GPIO_InitTypeDef	GPIO_InitStructre;														// 定义一个GPIO 配置结构体
	
	/* 时钟配置 */
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | 
	 RCC_APB2Periph_USART1, ENABLE);                                // 使能GPIOA端口时钟，使能UART1端口时钟
	
	/* GPIOA9 IO口复用USART1配置 */
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_9;												// 配置引脚为PA9
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AF_PP;									// 配置GPIO位复用推挽输出
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;								// 配置PA9引脚的输出速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructre);														// 将配置应用给PA9
	
	/* GPIOA10 IO口复用USART1配置 */
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_10;												// 配置引脚为PA10
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_IN_FLOATING;						// 配置GPIO为浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructre);														// 将配置应用给PA10
	
	/* USART1配置 */
	USART_InitStructre.USART_BaudRate = Baud;												// 设置波特率
	USART_InitStructre.USART_WordLength = USART_WordLength_8b;			// 设置传输的数据位位数
	USART_InitStructre.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// 使能USART具备收发数据的功能	
	USART_InitStructre.USART_StopBits = USART_StopBits_1;						// 设置在传输帧结尾设置一个位的停止位
	USART_InitStructre.USART_Parity = USART_Parity_No;							// 失能奇偶校验位
	USART_InitStructre.USART_HardwareFlowControl = 									// 无硬件数据流控制，不配置此位会出现接收不到数据
	 USART_HardwareFlowControl_None;
	
	// USART_StructInit(&USART_InitStructre); 											// 将USART_InitStructre配置按缺省值填入
	USART_Init(USART1, &USART_InitStructre);												// 初始化USART1配置
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									// 使能USART1的接收中断
	
	USART_Cmd(USART1,ENABLE);																				// 使能USART1串口
	
	/* NVIC配置 */
	Nvic_Config(USART1_IRQn, 0, 0, 1);															// 抢占优先级为0，响应优先级为0，并使能
	
}


// UART1发送数据
void Uart1_Send(char *Data) {
	
	// 当发送字符遇到\0时停止发送
	while (*Data != '\0') {
		while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
		USART_SendData(USART1, *(Data++));		// 调用USART_SendData发送单个字符
	}
	
}


// USART1接收数据<中断函数>
void USART1_IRQHandler() {
	
	char RxData;																// 定义一个接收单个字符的变量
	static int DataBit = 0;											// 定义一个接收位
	
	// 检查接收寄存器是否非空，非空为1，空为0
	FlagStatus ReceiveFlag = USART_GetITStatus(USART1, USART_IT_RXNE);
	
	if (ReceiveFlag != RESET) {
		
		RxData = USART_ReceiveData(USART1);				// 获取接收到的数据

		UsartReceiveData[DataBit++] = RxData;			// 将数据存入接收字符串中
		
		IsDownload = 1;														// 指示有数据开始下载进来
		
		// 当接收的数据遇到结尾字符时终止接收
		if (RxData == '\n') {
			UsartReceiveData[DataBit] = '\0';
			DataBit = 0;														// 清除接收位
			IsDownload = 0;													// 清除下载中标志位
			return;																	// 退出中断函数
		}
	}
}
