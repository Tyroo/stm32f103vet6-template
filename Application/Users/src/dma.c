/* DMA模块（验证通过） */

#include "dma.h"
#include "nvic.h"
#include "uart.h"


// 初始化DMA1，通道2用作获取USART3的接收数据到指定内存
void Dma1_Init(DMA_Channel_TypeDef *Channel, 
	uint32_t ReceveAddr, uint32_t SendAddr, u16 BuffSize) {
	
	/* 配置时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		// 使能DMA1的时钟
	
	/* 定义配置结构体 */
	DMA_InitTypeDef DMA_InitStructre;											// 定义DMA配置结构体
	
	/* DMA配置 */
	DMA_InitStructre.DMA_PeripheralBaseAddr = ReceveAddr;	// 设置DMA发送数据的外设基地址，外设寄存器地址为DMA数据传输的目的地
	DMA_InitStructre.DMA_MemoryBaseAddr = SendAddr;				// 设置DMA要存储数据的目标地址（DMA将从内存中拿到的数据传输到外设地址中）
	DMA_InitStructre.DMA_DIR = DMA_DIR_PeripheralDST;			// 设置DMA数据流向为从内存获取数据到外设中
	DMA_InitStructre.DMA_BufferSize = BuffSize;						// 设置一次DMA操作分多少次传输完数据(v=要传输的数据大小/DMA_MemoryDataSize) 
	DMA_InitStructre.DMA_MemoryInc = DMA_MemoryInc_Enable;									// 设置内存地址（目标地址）自增
	DMA_InitStructre.DMA_PeripheralInc = DMA_PeripheralInc_Disable;					// 设置外设地址（源地址）非自增
	DMA_InitStructre.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;					// 设置内存数据宽度(8Bit)
	DMA_InitStructre.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	// 设置外设的数据宽度(8Bit)
	DMA_InitStructre.DMA_Mode = DMA_Mode_Normal;														// 设置DMA工作在正常模式
	DMA_InitStructre.DMA_Priority = DMA_Priority_High;											// 设置通道的优先级为高
	DMA_InitStructre.DMA_M2M = DMA_M2M_Disable;															// 设置DMA为非内存到内存的传输（此设置中，数据是从USART3外设到内存的传输）
	
	/* 初始化配置 */
	DMA_Init(Channel, &DMA_InitStructre);															// 初始化DMA1通道配置
	
	/* 使能/失能中断 */
	DMA_ITConfig(Channel, DMA_IT_TC, ENABLE);							// 使能DMA的传输完成中断
	DMA_ITConfig(Channel, DMA_IT_TE, ENABLE);							// 使能DMA的传输错误中断
	
	/* 配置中断优先级 */
	Nvic_Config(DMA1_Channel4_IRQn, 0, 0, 1);													// 配置DMA1通道5的中断优先级
}


// 开启DMA的传输
void Dma_Start(DMA_Channel_TypeDef *Channel, u16 BuffSize) {
	DMA_Cmd(Channel, DISABLE); 									// 关闭 USART1 TX DMA1 所指示的通道 
	DMA_SetCurrDataCounter(Channel, BuffSize);	// 设置DMA的通道传输数据的次数，每次传输8位（1字节）
	DMA_Cmd(Channel, ENABLE);										// 使能DMA1的通道4，开始传输数据
}


// DMA1通道3<中断函数>
void DMA1_Channel4_IRQHandler() {
	
	ITStatus SucceedFlag = DMA_GetITStatus(DMA1_IT_TC4);	// 传输成功标志位
	ITStatus ErrorFlag = DMA_GetITStatus(DMA1_IT_TE4);		// 传输错误标志位
	
	// 传输成功
	if (SucceedFlag != RESET) {
		Uart1_Send("DMA Send Succeed!");
		DMA_ClearITPendingBit(DMA1_IT_TC4);	// 清除传输成功标志位
		DMA_ClearFlag(DMA1_FLAG_TC4);				// 清除DMA1通道3的传输完成标志位
	}
	
	// 传输失败
	if (ErrorFlag != RESET) {
		Uart1_Send("DMA Send Error!");
		DMA_ClearITPendingBit(DMA1_IT_TE4);	// 清除传输成功标志位
		DMA_ClearFlag(DMA1_FLAG_TE4);				// 清除DMA1通道3的传输错误标志位
	}
}
