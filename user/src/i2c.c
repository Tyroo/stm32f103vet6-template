/* ���IICģ�飨δ��֤�� */
#include "i2c.h"


void IIC_Init() {
	
	/* ���ýṹ�嶨�� */
	GPIO_InitTypeDef GPIO_InitStructre;											// ����һ��GPIO���ýṹ��
	
	/* ʹ��ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		// ʹ��GPIOBʱ��
	
	/* ����GPIO */
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP;					// GPIO�������
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;	// ����Pin10~11
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;				// ����ٶ�Ϊ50MHz
	
	/* ��ʼ��GPIO */
	GPIO_Init(GPIOB, &GPIO_InitStructre);										// Ӧ��GPIOB����
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);					// ��ʼ����SCK��Pin10����SDA��Pin11��
}


// ������ʼ�źţ�SCK�ߵ�ƽ�£�SDA�ɸ߱��
void IIC_Start() {
	
	IIC_Mode_Tx();	// ����I2CΪ����ģʽ
	
	IIC_SCL = 1, IIC_SDA_OUT = 1;		// ����SCL��SDA��׼��������ʼ�ź�
	// ��ʱ4us
	IIC_SDA_OUT = 0;								// ��SCL�ߵ�ƽʱ������SDA��������ʼ�ź�
	// ��ʱ4us
	IIC_SCL = 0;										// ��SCL���ͣ�׼����������
	
}


// ���ͽ����źţ�SCK�ߵ�ƽ�£�SDA�ɵͱ��
void IIC_Stop() {
	
	IIC_Mode_Tx();	// ����I2CΪ����ģʽ
	
	IIC_SCL = 0, IIC_SDA_OUT = 0;		// ����SCL������SDA
	
	Delay_Us(4);
	IIC_SCL = 1, IIC_SDA_OUT = 1;		// ����SDA�����������ź�
	
	Delay_Us(4);
}


// ����Ӧ���źţ����������ݺ���һ���͵�ƽ
void IIC_SendAck(void){ 
	
	IIC_Mode_Tx();
	
	IIC_SCL = 0;
	
	IIC_SDA_OUT = 0;
	
	Delay_Us(2);
	IIC_SCL = 1;
	
	Delay_Us(2);
	IIC_SCL = 0;
}


bool IIC_WaitAck(void) {
	
	u8 TimeoutCount = 0;	// ���豸Ӧ��ʱ����
	
	IIC_Mode_Rx(); 				// SDA����Ϊ���� 
	
	// ��SDA��SCL��Ϊ�ߵ�ƽ���ȴ����豸����SDAΪ�͵�ƽ��Ӧ���ź�
	IIC_SDA_OUT = 1;
	Delay_Us(1);
	
	IIC_SCL=1;
	Delay_Us(1);
	
	// �ȴ����豸��SDA����
	while(IIC_SDA_IN) {
		
		TimeoutCount++;
		
		// ������Ӧ��ȴ�ʱ�䳬��250��ʱ�����ں���Ϊͨ��ʧ��
		if(TimeoutCount>250) { 
			IIC_Stop();	// ����ͨ��ֹͣ�źŸ����豸
			return False;
		}
	}
	
	IIC_SCL = 0; //ʱ����� 0 
	
	return True; 
} 



// ������Ӧ���źţ����������ݺ���һ���ߵ�ƽ
void IIC_NotAck(void){ 
	
	IIC_Mode_Tx();
	
	IIC_SCL = 0;
	
	IIC_SDA_OUT = 1;
	
	Delay_Us(2);
	IIC_SCL = 1;
	
	Delay_Us(2);
	IIC_SCL = 0;
}


// ����8λ����
void IIC_Send_Byte(u8 Data) {
	
	IIC_Mode_Tx();	// ��IIC����Ϊ����ģʽ
	
	IIC_SCL = 0;		// ����SCL��ƽ��׼�����͵�һ֡����
	
	for(int i=7;i>=0;i--) {
		
		if (Data&(1<<i)) IIC_SDA_OUT = 1;
		else IIC_SDA_OUT = 0;
		
		Delay_Us(2);
		IIC_SCL = 1;
		
		Delay_Us(2);
		IIC_SCL = 0;
		
		Delay_Us(2);
	}
}


// ����8λ����
u8 IIC_Read_Byte(short IsAck) {
	
	static u8 RxData = 0;
	short RxIndex;
	
	IIC_Mode_Rx();
	
	for (RxIndex=0;RxIndex<8;RxIndex++) {
		
		IIC_SCL = 0;
		
		Delay_Us(2);
		IIC_SCL = 1;
		
		RxData <<= 1;
		if (IIC_SDA_IN) RxData |= 0x01;
	}
	
	if(!IsAck) {
		IIC_NotAck();
	} else {
		IIC_SendAck();
	}
	
	return RxData
}


// ����һ���ַ��������豸
bool IIC_Send_String(u8 *Str, u8 Addr) {
	
	bool WaitSignal;						// Ӧ���־λ
	
	IIC_Start();								// ����IIC��ʼ�ź�
	
	WaitSignal = IIC_WaitAck();	// ��ȡӦ���ź�
	
	if (WaitSignal == False) {	// ��δ��ȡӦ���ź�ʱ��ֹ���ͣ�����ʧ��
		return False;
	}
	
	IIC_Send_Byte(Addr>>8);				// ����Ŀ���ַ��λ
	IIC_WaitAck();							// Ӧ�����
	
	IIC_Send_Byte(Addr%256); 		// ���͵͵�ַ
	IIC_WaitAck(); 							// �ȴ�Ӧ��
	
	// �����������ַ���ֹͣ����
	while(*Str != '\n')
		IIC_Send_Byte(*Str++);		// ����һ���ַ�
	
	IIC_Stop();		// ����IIC�����ź�
	
	return True;
}


// ����һ���ַ���
u8 IIC_ReadString(u16 Addr, u8 StrLen, u8 StartSignal) {
	
	static u8 RxData[IIC_DATA_SIZE_MAX];
	u8 DataIndex = 0;
	
	if (StrLen>IIC_DATA_SIZE_MAX) return 0;
	
	IIC_Start();										// ����IIC��ʼ�ź�
	
	while(DataIndex<StrLen) {
	
		IIC_WaitAck();
		IIC_Send_Byte(Addr%256); 			//���͵͵�ַ
		
		IIC_WaitAck(); 
		IIC_Start(); 
		
		IIC_Send_Byte(StartSignal); 	//�������ģʽ 
		IIC_WaitAck();
		
		RxData[DataIndex] = IIC_Read_Byte(8);
		
		IIC_Stop();										// ֹͣ����
		DataIndex++;
	}
}
