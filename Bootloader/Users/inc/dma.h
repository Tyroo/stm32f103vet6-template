#ifndef __DMA_H__
#define __DMA_H__


/**
* @include
**/
#include "stm32f10x.h"


/**
* @function
* 作用：初始化DMA1，通道2用作获取USART3的接收数据到指定内存
* 参数：{ *Channel：DMA通道；ReceveAddr：数据目的地址；SendAddr：数据源地址；BuffSize：数据传输次数；}
* 返回值：void
**/
void Dma1_Init(DMA_Channel_TypeDef *Channel, 
	uint32_t ReceveAddr, uint32_t SendAddr, u16 BuffSize);



/**
* @function
* 作用：开启DMA的传输
* 参数：{ *Channel：DMA通道；BuffSize：数据传输次数；}
* 返回值：void
**/
void Dma_Start(DMA_Channel_TypeDef *Channel, u16 BuffSize);

#endif
