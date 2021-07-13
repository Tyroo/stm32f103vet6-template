/* DMAģ�飨δ��֤�� */

#include "dma.h"
#include "nvic.h"


// ��ʼ��DMA1��ͨ��2������ȡUSART3�Ľ������ݵ�ָ���ڴ�
void Dma1_Init(DMA_Channel_TypeDef *Channel, 
	uint32_t ReceveAddr, uint32_t SendAddr, u16 BuffSize) {
	
	/* ����ʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		// ʹ��DMA1��ʱ��
	
	/* �������ýṹ�� */
	DMA_InitTypeDef DMA_InitStructre;											// ����DMA���ýṹ��
	
	/* DMA���� */
	DMA_InitStructre.DMA_PeripheralBaseAddr = SendAddr;		// ����DMA��ȡ���ݵ��������ַ������USART3ΪDMA���ݵ���Դ
	DMA_InitStructre.DMA_MemoryBaseAddr = ReceveAddr;			// ����DMAҪ�洢���ݵ�Ŀ���ַ��DMA���õ������ݴ洢�����ڴ��ַ�У�
	DMA_InitStructre.DMA_DIR = DMA_DIR_PeripheralSRC;			// ����DMA��������Ϊ�������ȡ���ݵ��ڴ���
	DMA_InitStructre.DMA_BufferSize = BuffSize;						// ����һ��DMA�����ֶ��ٴδ���������(v=Ҫ��������ݴ�С/DMA_MemoryDataSize) 
	DMA_InitStructre.DMA_MemoryInc = DMA_PeripheralInc_Enable;							// �����ڴ��ַ��Ŀ���ַ������
	DMA_InitStructre.DMA_PeripheralInc = DMA_PeripheralInc_Disable;					// ���������ַ��Դ��ַ��������
	DMA_InitStructre.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;					// �����ڴ����ݿ��
	DMA_InitStructre.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	// ������������ݿ��
	DMA_InitStructre.DMA_Mode = DMA_Mode_Normal;														// ����DMA����������ģʽ
	DMA_InitStructre.DMA_Priority = DMA_Priority_High;											// ����ͨ�������ȼ�
	DMA_InitStructre.DMA_M2M = DMA_M2M_Disable;															// ����DMAΪ���ڴ浽�ڴ�Ĵ��䣨�������У������Ǵ�USART3���赽�ڴ�Ĵ��䣩
	
	/* ��ʼ������ */
	DMA_Init(Channel, &DMA_InitStructre);															// ��ʼ��DMA1ͨ��2����
	
	/* ʹ��/ʧ�� */
	DMA_Cmd(Channel, DISABLE);																				// ʧ��DMA1��ͨ��2
	DMA_ITConfig(Channel, DMA_IT_TC | DMA_IT_TE, ENABLE);							// ʹ��DMA�Ĵ�����ɡ���������ж�
	
	/* �����ж����ȼ� */
	Nvic_Config(DMA1_Channel3_IRQn, 0, 0, 1);													// ����DMA1ͨ��3���ж����ȼ�
	
	/*
	*	������USART3��ʼ�������ӣ�USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE)��ʹ��USART3 DMA���չ���
	*/
}


// ����DMA�Ĵ���
void Dma_Start(DMA_Channel_TypeDef *Channel, u16 BuffSize) {
	
	DMA_SetCurrDataCounter(Channel, BuffSize);	// ����DMA��ͨ���������ݵĴ�����ÿ�δ���8λ��1�ֽڣ�
	DMA_Cmd(Channel, ENABLE);										// ʹ��DMA1��ͨ��2����ʼ��������
}


// DMA1ͨ��3<�жϺ���>
void DMA1_Channel3_IRQHandler() {
	
	ITStatus SucceedFlag = DMA_GetITStatus(DMA_IT_TC);	// ����ɹ���־λ
	ITStatus ErrorFlag = DMA_GetITStatus(DMA_IT_TE);		// ��������־λ
	
	if (SucceedFlag != RESET) {
		// ����ɹ�
	}
	
	if (ErrorFlag != RESET) {
		// ����ʧ��
	}
}
