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
	
	I2C_Mode_Tx();	// ����I2CΪ����ģʽ
	
	IIC_SCL = 1, IIC_SDA_OUT = 1;		// ����SCL��SDA��׼��������ʼ�ź�
	// ��ʱ4us
	IIC_SDA_OUT = 0;					// ��SCL�ߵ�ƽʱ������SDA��������ʼ�ź�
	// ��ʱ4us
	IIC_SCL = 0;					// ��SCL���ͣ�׼����������
	
}


// ���ͽ����źţ�SCK�ߵ�ƽ�£�SDA�ɵͱ��
void IIC_Stop() {
	
	I2C_Mode_Tx();	// ����I2CΪ����ģʽ
	
	IIC_SCL = 0, IIC_SDA_OUT = 0;		// ����SCL������SDA
	
	Delay_Us(4);
	IIC_SCL = 1, IIC_SDA_OUT = 1;					// ����SDA�����������ź�
	
	Delay_Us(4);
}


// ������Ӧ���ź�
void IIC_Ack(void){ 
	
	I2C_Mode_Tx();
	
	IIC_SCL = 0;
	
	IIC_SDA_OUT = 0;
	
	Delay_Us(2);
	IIC_SCL = 1;
	
	Delay_Us(2);
	IIC_SCL = 0;
}



// ������Ӧ���ź�
void IIC_NotAck(void){ 
	
	I2C_Mode_Tx();
	
	IIC_SCL = 0;
	
	IIC_SDA_OUT = 1;
	
	Delay_Us(2);
	IIC_SCL = 1;
	
	Delay_Us(2);
	IIC_SCL = 0;
}


// ����8λ����
void Send_Data_Byte(u8 Data) {
	
	I2C_Mode_Tx();	// ��IIC����Ϊ����ģʽ
	
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
void Read_Data_Byte(short IsAck) {
	
	static unsigned char RxData = 0;
	short RxIndex;
	
	I2C_Mode_Rx();
	
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
		IIC_Ack();
	}
}
