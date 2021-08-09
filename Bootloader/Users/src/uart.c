/** USART�շ�����ģ�飨��֤ͨ���� **/
#include <string.h>
#include "uart.h"
#include "nvic.h"


// USART1���յ�����
u16 UsartReceiveDataOne[100];
u16 UsartReceiveDataTwo[100];

// �Ƿ������ر�־
u8 IsDownload = 0;

// ��ʼ��UART
void Uart1_Init(int Baud) {
	
	/* ���ýṹ��ָ�붨�� */
	USART_InitTypeDef USART_InitStructre;														// ����һ��USART���ýṹ��
	GPIO_InitTypeDef	GPIO_InitStructre;														// ����һ��GPIO ���ýṹ��
	
	/* ʱ������ */
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | 
	 RCC_APB2Periph_USART1, ENABLE);                                // ʹ��GPIOA�˿�ʱ�ӣ�ʹ��UART1�˿�ʱ��
	
	/* GPIOA9 IO�ڸ���USART1���� */
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_9;												// ��������ΪPA9
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AF_PP;									// ����GPIOλ�����������
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;								// ����PA9���ŵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructre);														// ������Ӧ�ø�PA9
	
	/* GPIOA10 IO�ڸ���USART1���� */
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_10;												// ��������ΪPA10
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_IN_FLOATING;						// ����GPIOΪ��������
	GPIO_Init(GPIOA, &GPIO_InitStructre);														// ������Ӧ�ø�PA10
	
	/* USART1���� */
	USART_InitStructre.USART_BaudRate = Baud;												// ���ò�����
	USART_InitStructre.USART_WordLength = USART_WordLength_8b;			// ���ô��������λλ��
	USART_InitStructre.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// ʹ��USART�߱��շ����ݵĹ���	
	USART_InitStructre.USART_StopBits = USART_StopBits_1;						// �����ڴ���֡��β����һ��λ��ֹͣλ
	USART_InitStructre.USART_Parity = USART_Parity_No;							// ʧ����żУ��λ
	USART_InitStructre.USART_HardwareFlowControl = 									// ��Ӳ�����������ƣ������ô�λ����ֽ��ղ�������
	 USART_HardwareFlowControl_None;
	
	// USART_StructInit(&USART_InitStructre); 											// ��USART_InitStructre���ð�ȱʡֵ����
	USART_Init(USART1, &USART_InitStructre);												// ��ʼ��USART1����
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									// ʹ��USART1�Ľ����ж�
	
	USART_Cmd(USART1,ENABLE);																				// ʹ��USART1����
	
	/* NVIC���� */
	Nvic_Config(USART1_IRQn, 0, 0, 1);															// ��ռ���ȼ�Ϊ0����Ӧ���ȼ�Ϊ0����ʹ��
	
}


// UART1��������
void Uart1_Send(char *Data) {
	
	// �������ַ�����\0ʱֹͣ����
	while (*Data != '\0') {
		while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
		USART_SendData(USART1, *(Data++));		// ����USART_SendData���͵����ַ�
	}
	
}


// USART1��������<�жϺ���>
void USART1_IRQHandler() {
	
	char RxData;																// ����һ�����յ����ַ��ı���
	static int DataBit = 0;											// ����һ������λ
	
	// �����ռĴ����Ƿ�ǿգ��ǿ�Ϊ1����Ϊ0
	FlagStatus ReceiveFlag = USART_GetITStatus(USART1, USART_IT_RXNE);
	
	if (ReceiveFlag != RESET) {
		
		RxData = USART_ReceiveData(USART1);				// ��ȡ���յ�������

		UsartReceiveData[DataBit++] = RxData;			// �����ݴ�������ַ�����
		
		IsDownload = 1;														// ָʾ�����ݿ�ʼ���ؽ���
		
		// �����յ�����������β�ַ�ʱ��ֹ����
		if (RxData == '\n') {
			UsartReceiveData[DataBit] = '\0';
			DataBit = 0;														// �������λ
			IsDownload = 0;													// ��������б�־λ
			return;																	// �˳��жϺ���
		}
	}
}
