#include "can.h"


uint8_t CAN1_Rx_Buff[50];


// CAN1配置函数
void CAN1_Config(void) {
	
	/* 配置结构体定义 */
	CAN_InitTypeDef CAN_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStruct;
	
	/* 时钟使能 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	// 使能GPIOA复用时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// 使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);	// 使能CAN1时钟
	
	/* GPIO配置 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;// 引脚Pin11、Pin12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				// 复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// 速度100MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_Remap2_CAN1, ENABLE);				// 引脚重映射
	
	/* CAN1配置 */
	// CAN基本配置
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	// 设置CAN为正常模式
	CAN_InitStructure.CAN_Prescaler = 5;					// 分频系数
	CAN_InitStructure.CAN_ABOM = DISABLE;					// 软件自动离线管理关闭
	CAN_InitStructure.CAN_AWUM = DISABLE;					// 睡眠模式通过软件唤醒
	CAN_InitStructure.CAN_NART = ENABLE;					// 禁止报文自动传输
	CAN_InitStructure.CAN_RFLM = DISABLE;					// 报文不锁定，新房覆盖旧的
	CAN_InitStructure.CAN_TTCM = DISABLE;					// 非时间触发通信模式
	CAN_InitStructure.CAN_TXFP = DISABLE;					// 优先级由报文标识符决定
	// 配置CAN1波特率为500KHz
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;			// 重新同步跳跃宽度为1个Tq
	CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;			// 时间段1占用5个Tq
	CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;			// 时间段1占用4个Tq
	CAN_Init(CAN1, &CAN_InitStructure);						// 初始化CAN1配置
	
	// CAN滤波器配置
	CAN_FilterInitStruct.CAN_FilterMode = 0;				// 掩码模式
	CAN_FilterInitStruct.CAN_FilterIdHigh = 0x0000;			// 期望值高位
	CAN_FilterInitStruct.CAN_FilterIdLow = 0x0000;			// 期望值低位
	CAN_FilterInitStruct.CAN_FilterMaskIdHigh = 0x0000;		// 期望值高位
	CAN_FilterInitStruct.CAN_FilterMaskIdLow = 0x0000;		// 期望值低位
	CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;	// 关联FIFO
	CAN_FilterInitStruct.CAN_FilterNumber = 0;							// 选择过滤器0
	CAN_FilterInitStruct.CAN_FilterScale = CAN_FilterScale_32bit;		// 32位模式
	CAN_FilterInitStruct.CAN_FilterActivation = ENABLE;					// 激活过滤器0
	CAN_FilterInit(&CAN_FilterInitStruct);					// 初始化CAN过滤器
	
	/* 中断配置 */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);				// 开启CAN1接收挂号中断
	Nvic_Config(USB_LP_CAN1_RX0_IRQn, 0, 0, ENABLE);				// 配置中断优先级并使能
}


// CAN1接收中断函数
void USB_LP_CAN1_RX0_IRQHandler(void) {
	
	u8 RxIndex;
	CanRxMsg RxMsg;
	
	CAN_Receive(CAN1, CAN_FIFO0, &RxMsg);
	
	for(RxIndex=0;RxIndex<RxMsg.DLC;RxIndex++) {
		CAN1_Rx_Buff[RxIndex] = RxMsg.Data[RxIndex];
	}
}


// CAN发送接口函数
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
