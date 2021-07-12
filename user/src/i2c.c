/* ���IICģ�� */
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
	
	SCL_H, SDA_H;		// ����SCL��SDA��׼��������ʼ�ź�
	// ��ʱ4us
	SDA_L;					// ��SCL�ߵ�ƽʱ������SDA��������ʼ�ź�
	// ��ʱ4us
	SCL_L;					// ��SCL���ͣ�׼����������
	
}


// ���ͽ����źţ�SCK�ߵ�ƽ�£�SDA�ɵͱ��
void IIC_Stop() {
	
	I2C_Mode_Tx();	// ����I2CΪ����ģʽ
	
	SCL_L, SDA_L;		// ����SCL������SDA
	// ��ʱ4us
	SCL_H, SDA_H;					// ����SDA�����������ź�
	// ��ʱ4us
}


// ������Ӧ���ź�
void IIC_Ack(void){ 
	
	I2C_Mode_Tx();
	
	SCL_L;
	
	SDA_L;
	// ��ʱ2us
	SCL_H;
	// ��ʱ2us
	SCL_L;
}



// ������Ӧ���ź�
void IIC_NotAck(void){ 
	
	I2C_Mode_Tx();
	
	SCL_L;
	
	SDA_H;
	// ��ʱ2us
	SCL_H;
	// ��ʱ2us
	SCL_L;
}


// ����8λ����
void Send_Data_8Bit(u8 Data) {
	
	IIC_Start();	// ��������֮ǰ������һ����ʼ�ź�
	
	for(int i=7;i>=0;i--) {
		
		if (Data&(1<<i)) SDA_H;
		else SDA_L;
		
		// ��ʱ2us
		SCL_H;
		// ��ʱ2us
		SCL_L;
		// ��ʱ2us
	}
}
