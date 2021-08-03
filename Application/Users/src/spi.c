/* SPIͨ��ģ�飨��֤ͨ���� */
#include "spi.h"


u8 SpiReceiveData[50];

// SPI1��ʼ������
void Spi1_Init() {
	
	/* ���ýṹ�嶨�� */
	SPI_InitTypeDef SPI_InitStructure;																	// ����SPI���ýṹ��
	GPIO_InitTypeDef GPIO_InitStructure;																// ����GPIO���ýṹ��
	
	/* ʱ��ʹ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE); 
// ʹ��SPI1��GPIOA�ж�
	
	/* ����GPIO */
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;											// ��IO������Ϊ�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;										// ��������ٶ�Ϊ50MHz

	/* ����SPI1 */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	// ����Ϊ2��˫��ȫ˫��ģʽ
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;												// ����Ϊ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;// ����SPI�������ʣ�����=72MHz/v��
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;										// SPI���δ����������
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;												// ��ʱ�ӵĵڶ��������زɼ�����
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;													// ����SPIʱ���ڵ͵�ƽʱΪ����״̬
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;									// �������ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;														// ����NSS�ź����������
	SPI_InitStructure.SPI_CRCPolynomial = 7;														// RCRУ�����ʽ������1����
	
	/* ��ʼ������ */
	GPIO_Init(GPIOA, &GPIO_InitStructure);															// ��ʼ��GPIOA5��6��7����
	SPI_Init(SPI1, &SPI_InitStructure);																	// ��ʼ��SPI1����
	
	/* ʹ��/ʧ�� */
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);										// ʹ��SPI1���ܷǿ��ж�
	SPI_Cmd(SPI1, ENABLE);																							// ʹ��SPI1����
	Nvic_Config(SPI1_IRQn, 1, 1, ENABLE);																// ����SPI�ж����ȼ�
	
}


// ʹ��SPI1��������
bool SPI1_Send(u8* SendData) {
	
	// ��û�����������ַ�ʱһֱ����
	while(*SendData != '\0') {
		// �ȴ����ͻ��������
		while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
		
		SPI_I2S_SendData(SPI1, *(SendData++));
	}
	return True;
}


// SPI1ͨ��<�жϺ���>
void SPI1_IRQHandler() {
	
	u8 RxData;							// ����һ������ÿ���ֽڵı���
	static u8 RxIndex = 0;	// �������������
	// SPI���ջ������ǿձ�־
	FlagStatus ReadFlag = SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE);
	
	// �����жϺ󣬵����ܻ�������Ϊ��
	if (ReadFlag != RESET) {
		RxData = SPI_I2S_ReceiveData(SPI1);	// ��ȡ���ջ�������ֵ
		SpiReceiveData[RxIndex++] = RxData;	// �����������������
		
		// �����������ַ�����ֹ����
		if (RxData == '\n') {
			RxIndex = 0;
			SpiReceiveData[RxIndex-1] = '\0'; // �����λ����Ϊ�����ַ�
			return;
		}
	}
}
