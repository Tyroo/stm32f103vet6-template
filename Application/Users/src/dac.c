/* DAC模块 */
#include "dac.h"


void Dac_Init() {
	
	// ...
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


// 生成正弦波对应的定时器计数值数组，使用IQmathLib库加速浮点运算
int Dac_GenerateCntValue_Sin(u8 SampNum) {
	
	int SinValueArray[SampNum];	// 正弦函数对应的计数值数组
	_iq IQRatio;								// 占圆周率的比例（IQ值）
	_iq IQSinValue;							// 正弦函数对应的计数值（IQ值）
	
	// 计算每个点的定时器计数值，存入数组中
	for(u8 N=0;N<SampNum;N++) {
		IQRatio = _IQdiv(N, 90);
		IQSinValue = _IQmpy(4000, _IQsinPU(IQRatio));
		SinValueArray[N] = (int)_IQint(IQSinValue);
	}
	
	return *SinValueArray;
}

