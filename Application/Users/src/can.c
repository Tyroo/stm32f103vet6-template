#include "can.h"


uint8_t CAN1_Rx_Buff[50];


// CAN1���ú���
void CAN1_Config(void) {
	
	/* ���ýṹ�嶨�� */
	CAN_InitTypeDef CAN_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStruct;
	
	/* ʱ��ʹ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	// ʹ��GPIOA����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);	// ʹ��CAN1ʱ��
	
	/* GPIO���� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;// ����Pin11��Pin12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				// ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// �ٶ�100MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_Remap2_CAN1, ENABLE);				// ������ӳ��
	
	/* CAN1���� */
	// CAN��������
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	// ����CANΪ����ģʽ
	CAN_InitStructure.CAN_Prescaler = 5;					// ��Ƶϵ��
	CAN_InitStructure.CAN_ABOM = DISABLE;					// ����Զ����߹���ر�
	CAN_InitStructure.CAN_AWUM = DISABLE;					// ˯��ģʽͨ���������
	CAN_InitStructure.CAN_NART = ENABLE;					// ��ֹ�����Զ�����
	CAN_InitStructure.CAN_RFLM = DISABLE;					// ���Ĳ��������·����Ǿɵ�
	CAN_InitStructure.CAN_TTCM = DISABLE;					// ��ʱ�䴥��ͨ��ģʽ
	CAN_InitStructure.CAN_TXFP = DISABLE;					// ���ȼ��ɱ��ı�ʶ������
	// ����CAN1������Ϊ500KHz
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;			// ����ͬ����Ծ���Ϊ1��Tq
	CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;			// ʱ���1ռ��5��Tq
	CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;			// ʱ���1ռ��4��Tq
	CAN_Init(CAN1, &CAN_InitStructure);						// ��ʼ��CAN1����
	
	// CAN�˲�������
	CAN_FilterInitStruct.CAN_FilterMode = 0;				// ����ģʽ
	CAN_FilterInitStruct.CAN_FilterIdHigh = 0x0000;			// ����ֵ��λ
	CAN_FilterInitStruct.CAN_FilterIdLow = 0x0000;			// ����ֵ��λ
	CAN_FilterInitStruct.CAN_FilterMaskIdHigh = 0x0000;		// ����ֵ��λ
	CAN_FilterInitStruct.CAN_FilterMaskIdLow = 0x0000;		// ����ֵ��λ
	CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;	// ����FIFO
	CAN_FilterInitStruct.CAN_FilterNumber = 0;							// ѡ�������0
	CAN_FilterInitStruct.CAN_FilterScale = CAN_FilterScale_32bit;		// 32λģʽ
	CAN_FilterInitStruct.CAN_FilterActivation = ENABLE;					// ���������0
	CAN_FilterInit(&CAN_FilterInitStruct);					// ��ʼ��CAN������
	
	/* �ж����� */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);				// ����CAN1���չҺ��ж�
	Nvic_Config(USB_LP_CAN1_RX0_IRQn, 0, 0, ENABLE);				// �����ж����ȼ���ʹ��
}


// CAN1�����жϺ���
void USB_LP_CAN1_RX0_IRQHandler(void) {
	
	u8 RxIndex;
	CanRxMsg RxMsg;
	
	CAN_Receive(CAN1, CAN_FIFO0, &RxMsg);
	
	for(RxIndex=0;RxIndex<RxMsg.DLC;RxIndex++) {
		CAN1_Rx_Buff[RxIndex] = RxMsg.Data[RxIndex];
	}
}


// CAN���ͽӿں���
unsigned char CAN1_Send_Msg(CanTxMsg* TxMsg) {
	uint8_t MBox;
	uint16_t TxIndex;
	
	MBox = CAN_Transmit(CAN1, TxMsg);
	TxIndex = 0;
	
	while(CAN_TransmitStatus(CAN1, MBox) != CAN_TxStatus_Ok) {
		TxIndex++;
		if (TxIndex>=0xFFF) return 1;
	}
	
	return 0;
}
