#ifndef __DMA_H__
#define __DMA_H__


/**
* @include
**/
#include "stm32f10x.h"


/**
* @function
* ���ã���ʼ��DMA1��ͨ��2������ȡUSART3�Ľ������ݵ�ָ���ڴ�
* ������{ *Channel��DMAͨ����ReceveAddr������Ŀ�ĵ�ַ��SendAddr������Դ��ַ��BuffSize�����ݴ��������}
* ����ֵ��void
**/
void Dma1_Init(DMA_Channel_TypeDef *Channel, 
	uint32_t ReceveAddr, uint32_t SendAddr, u16 BuffSize);



/**
* @function
* ���ã�����DMA�Ĵ���
* ������{ *Channel��DMAͨ����BuffSize�����ݴ��������}
* ����ֵ��void
**/
void Dma_Start(DMA_Channel_TypeDef *Channel, u16 BuffSize);

#endif
