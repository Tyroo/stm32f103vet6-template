/* DACģ�飨��֤ͨ���� */
#include "dac.h"


const u8 DAC_CNT_RESOLUTION = 181;	// DAC�ļ���ֵ���鳤��

void Dac_Init() {
	
	/* ���ýṹ�嶨�� */
	GPIO_InitTypeDef GPIO_InitStructre; // GPIO���ýṹ�嶨��
	DAC_InitTypeDef DAC_InitStructre;		// DAC���ýṹ�嶨��
	
	/* ʹ��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* GPIO���� */
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_4;																	// PA4��ΪDAC1���
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	
	/* DAC���� */
	DAC_InitStructre.DAC_Trigger = DAC_Trigger_None;													// ��ʹ��Ӳ������ģʽ
	DAC_InitStructre.DAC_OutputBuffer = DAC_OutputBuffer_Disable;							// ��ʹ���������
	DAC_InitStructre.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;	// ��������/��ֵѡ����0��ʹ�ò��η�����ʱ��Ч
	DAC_InitStructre.DAC_WaveGeneration = DAC_WaveGeneration_None;						// ��ʹ�ò��η�����
	
	/* ���ó�ʼ�� */
	GPIO_Init(GPIOA, &GPIO_InitStructre);
	DAC_Init(DAC_Channel_1, &DAC_InitStructre);
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);																	// ����DAC�����Ĵ������Ϊ12λ�����Ҷ��룬��ʼֵΪ0
	
	/* ʹ��/ʧ�� */
	DAC_Cmd(DAC_Channel_1, ENABLE);																						// ʹ��DACͨ��1
	
}


// �������Ҳ���Ӧ�Ķ�ʱ������ֵ���飬ʹ��IQmathLib����ٸ�������
int* Dac_GenerCntArr_Sin() {
	
	static int SinValueArray[DAC_CNT_RESOLUTION];	// ���Һ�����Ӧ�ļ���ֵ����
	_iq IQRatio;																	// ռԲ���ʵı�����IQֵ��
	_iq IQSinValue;																// ���Һ�����Ӧ�ļ���ֵ��IQֵ��
	
	// ����ÿ����Ķ�ʱ������ֵ������������
	for(u8 N=0;N<DAC_CNT_RESOLUTION;N++) {
		IQRatio = _IQdiv(N, (DAC_CNT_RESOLUTION-1)/2);			// ��ǰ��ֵռ�е�ֵ��������Χ��0-200%������Ӧ��0-2�У�
		IQSinValue = _IQmpyI32int(2000, _IQsinPU(IQRatio));	// �����ֵ��ʽ��y1 = 2000 * sin(IQRatio * ��)
		SinValueArray[N] = 2000 + IQSinValue;								// �������ֵ���������У�y2 = 2000 + y1
	}
	
	return SinValueArray;
}




