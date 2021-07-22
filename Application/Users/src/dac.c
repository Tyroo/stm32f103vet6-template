/* DACģ�� */
#include "dac.h"


void Dac_Init() {
	
	// ...
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


// �������Ҳ���Ӧ�Ķ�ʱ������ֵ���飬ʹ��IQmathLib����ٸ�������
int Dac_GenerateCntValue_Sin(u8 SampNum) {
	
	int SinValueArray[SampNum];	// ���Һ�����Ӧ�ļ���ֵ����
	_iq IQRatio;								// ռԲ���ʵı�����IQֵ��
	_iq IQSinValue;							// ���Һ�����Ӧ�ļ���ֵ��IQֵ��
	
	// ����ÿ����Ķ�ʱ������ֵ������������
	for(u8 N=0;N<SampNum;N++) {
		IQRatio = _IQdiv(N, 90);
		IQSinValue = _IQmpy(4000, _IQsinPU(IQRatio));
		SinValueArray[N] = (int)_IQint(IQSinValue);
	}
	
	return *SinValueArray;
}

