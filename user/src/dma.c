/* DMA模块（未验证） */

#include "dma.h"
#include "nvic.h"


// 初始化DMA1，通道2用作获取USART3的接收数据到指定内存
void Dma1_Init(DMA_Channel_TypeDef *Channel, 
	uint32_t ReceveAddr, uint32_t SendAddr, u16 BuffSize) {
	
	/* 配置时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		// 使能DMA1的时钟
	
	/* 定义配置结构体 */
	DMA_InitTypeDef DMA_InitStructre;											// 定义DMA配置结构体
	
	/* DMA配置 */
	DMA_InitStructre.DMA_PeripheralBaseAddr = SendAddr;		// 设置DMA获取数据的外设基地址，外设USART3为DMA数据的来源
	DMA_InitStructre.DMA_MemoryBaseAddr = ReceveAddr;			// 设置DMA要存储数据的目标地址（DMA将拿到的数据存储到该内存地址中）
	DMA_InitStructre.DMA_DIR = DMA_DIR_PeripheralSRC;			// 设置DMA数据流向为从外设获取数据到内存中
	DMA_InitStructre.DMA_BufferSize = BuffSize;						// 设置一次DMA操作分多少次传输完数据(v=要传输的数据大小/DMA_MemoryDataSize) 
	DMA_InitStructre.DMA_MemoryInc = DMA_PeripheralInc_Enable;							// 设置内存地址（目标地址）自增
	DMA_InitStructre.DMA_PeripheralInc = DMA_PeripheralInc_Disable;					// 设置外设地址（源地址）非自增
	DMA_InitStructre.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;					// 设置内存数据宽度
	DMA_InitStructre.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	// 设置外设的数据宽度
	DMA_InitStructre.DMA_Mode = DMA_Mode_Normal;														// 设置DMA工作在正常模式
	DMA_InitStructre.DMA_Priority = DMA_Priority_High;											// 设置通道的优先级
	DMA_InitStructre.DMA_M2M = DMA_M2M_Disable;															// 设置DMA为非内存到内存的传输（此设置中，数据是从USART3外设到内存的传输）
	
	/* 初始化配置 */
	DMA_Init(Channel, &DMA_InitStructre);															// 初始化DMA1通道2配置
	
	/* 使能/失能 */
	DMA_Cmd(Channel, DISABLE);																				// 失能DMA1的通道2
	DMA_ITConfig(Channel, DMA_IT_TC | DMA_IT_TE, ENABLE);							// 使能DMA的传输完成、传输错误中断
	
	/* 配置中断优先级 */
	Nvic_Config(DMA1_Channel3_IRQn, 0, 0, 1);													// 配置DMA1通道3的中断优先级
	
	/*
	*	需在在USART3初始化中增加：USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE)，使能USART3 DMA接收功能
	*/
}


// 开启DMA的传输
void Dma_Start(DMA_Channel_TypeDef *Channel, u16 BuffSize) {
	
	DMA_SetCurrDataCounter(Channel, BuffSize);	// 设置DMA的通道传输数据的次数，每次传输8位（1字节）
	DMA_Cmd(Channel, ENABLE);										// 使能DMA1的通道2，开始传输数据
}


// DMA1通道3<中断函数>
void DMA1_Channel3_IRQHandler() {
	
	ITStatus SucceedFlag = DMA_GetITStatus(DMA_IT_TC);	// 传输成功标志位
	ITStatus ErrorFlag = DMA_GetITStatus(DMA_IT_TE);		// 传输错误标志位
	
	if (SucceedFlag != RESET) {
		// 传输成功
	}
	
	if (ErrorFlag != RESET) {
		// 传输失败
	}
}
