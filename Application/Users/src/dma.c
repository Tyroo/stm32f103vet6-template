/* DMAģ�飨��֤ͨ���� */

#include "dma.h"
#include "nvic.h"
#include "uart.h"


// ��ʼ��DMA1��ͨ��2������ȡUSART3�Ľ������ݵ�ָ���ڴ�
void Dma1_Init(DMA_Channel_TypeDef *Channel, 
	uint32_t ReceveAddr, uint32_t SendAddr, u16 BuffSize) {
	
	/* ����ʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		// ʹ��DMA1��ʱ��
	
	/* �������ýṹ�� */
	DMA_InitTypeDef DMA_InitStructre;											// ����DMA���ýṹ��
	
	/* DMA���� */
	DMA_InitStructre.DMA_PeripheralBaseAddr = ReceveAddr;	// ����DMA�������ݵ��������ַ������Ĵ�����ַΪDMA���ݴ����Ŀ�ĵ�
	DMA_InitStructre.DMA_MemoryBaseAddr = SendAddr;				// ����DMAҪ�洢���ݵ�Ŀ���ַ��DMA�����ڴ����õ������ݴ��䵽�����ַ�У�
	DMA_InitStructre.DMA_DIR = DMA_DIR_PeripheralDST;			// ����DMA��������Ϊ���ڴ��ȡ���ݵ�������
	DMA_InitStructre.DMA_BufferSize = BuffSize;						// ����һ��DMA�����ֶ��ٴδ���������(v=Ҫ��������ݴ�С/DMA_MemoryDataSize) 
	DMA_InitStructre.DMA_MemoryInc = DMA_MemoryInc_Enable;									// �����ڴ��ַ��Ŀ���ַ������
	DMA_InitStructre.DMA_PeripheralInc = DMA_PeripheralInc_Disable;					// ���������ַ��Դ��ַ��������
	DMA_InitStructre.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;					// �����ڴ����ݿ��(8Bit)
	DMA_InitStructre.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	// ������������ݿ��(8Bit)
	DMA_InitStructre.DMA_Mode = DMA_Mode_Normal;														// ����DMA����������ģʽ
	DMA_InitStructre.DMA_Priority = DMA_Priority_High;											// ����ͨ�������ȼ�Ϊ��
	DMA_InitStructre.DMA_M2M = DMA_M2M_Disable;															// ����DMAΪ���ڴ浽�ڴ�Ĵ��䣨�������У������Ǵ�USART3���赽�ڴ�Ĵ��䣩
	
	/* ��ʼ������ */
	DMA_Init(Channel, &DMA_InitStructre);															// ��ʼ��DMA1ͨ������
	
	/* ʹ��/ʧ���ж� */
	DMA_ITConfig(Channel, DMA_IT_TC, ENABLE);							// ʹ��DMA�Ĵ�������ж�
	DMA_ITConfig(Channel, DMA_IT_TE, ENABLE);							// ʹ��DMA�Ĵ�������ж�
	
	/* �����ж����ȼ� */
	Nvic_Config(DMA1_Channel4_IRQn, 0, 0, 1);													// ����DMA1ͨ��5���ж����ȼ�
}


// ����DMA�Ĵ���
void Dma_Start(DMA_Channel_TypeDef *Channel, u16 BuffSize) {
	DMA_Cmd(Channel, DISABLE); 									// �ر� USART1 TX DMA1 ��ָʾ��ͨ�� 
	DMA_SetCurrDataCounter(Channel, BuffSize);	// ����DMA��ͨ���������ݵĴ�����ÿ�δ���8λ��1�ֽڣ�
	DMA_Cmd(Channel, ENABLE);										// ʹ��DMA1��ͨ��4����ʼ��������
}


// DMA1ͨ��3<�жϺ���>
void DMA1_Channel4_IRQHandler() {
	
	ITStatus SucceedFlag = DMA_GetITStatus(DMA1_IT_TC4);	// ����ɹ���־λ
	ITStatus ErrorFlag = DMA_GetITStatus(DMA1_IT_TE4);		// ��������־λ
	
	// ����ɹ�
	if (SucceedFlag != RESET) {
		Uart1_Send("DMA Send Succeed!");
		DMA_ClearITPendingBit(DMA1_IT_TC4);	// �������ɹ���־λ
		DMA_ClearFlag(DMA1_FLAG_TC4);				// ���DMA1ͨ��3�Ĵ�����ɱ�־λ
	}
	
	// ����ʧ��
	if (ErrorFlag != RESET) {
		Uart1_Send("DMA Send Error!");
		DMA_ClearITPendingBit(DMA1_IT_TE4);	// �������ɹ���־λ
		DMA_ClearFlag(DMA1_FLAG_TE4);				// ���DMA1ͨ��3�Ĵ�������־λ
	}
}
