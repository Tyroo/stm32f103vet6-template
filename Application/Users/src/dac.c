/* DAC模块（验证通过） */
#include "dac.h"


const u8 DAC_CNT_RESOLUTION = 181;	// DAC的计数值数组长度

void Dac_Init() {
	
	/* 配置结构体定义 */
	GPIO_InitTypeDef GPIO_InitStructre; // GPIO配置结构体定义
	DAC_InitTypeDef DAC_InitStructre;		// DAC配置结构体定义
	
	/* 使能时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* GPIO配置 */
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_4;																	// PA4作为DAC1输出
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	
	/* DAC配置 */
	DAC_InitStructre.DAC_Trigger = DAC_Trigger_None;													// 不使用硬件触发模式
	DAC_InitStructre.DAC_OutputBuffer = DAC_OutputBuffer_Disable;							// 不使用输出缓存
	DAC_InitStructre.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;	// 设置屏蔽/幅值选择器0，使用波形发生器时生效
	DAC_InitStructre.DAC_WaveGeneration = DAC_WaveGeneration_None;						// 不使用波形发生器
	
	/* 配置初始化 */
	GPIO_Init(GPIOA, &GPIO_InitStructre);
	DAC_Init(DAC_Channel_1, &DAC_InitStructre);
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);																	// 设置DAC计数寄存器宽度为12位，且右对齐，初始值为0
	
	/* 使能/失能 */
	DAC_Cmd(DAC_Channel_1, ENABLE);																						// 使能DAC通道1
	
}


// 生成正弦波对应的定时器计数值数组，使用IQmathLib库加速浮点运算
int* Dac_GenerCntArr_Sin() {
	
	static int SinValueArray[DAC_CNT_RESOLUTION];	// 正弦函数对应的计数值数组
	_iq IQRatio;																	// 占圆周率的比例（IQ值）
	_iq IQSinValue;																// 正弦函数对应的计数值（IQ值）
	
	// 计算每个点的定时器计数值，存入数组中
	for(u8 N=0;N<DAC_CNT_RESOLUTION;N++) {
		IQRatio = _IQdiv(N, (DAC_CNT_RESOLUTION-1)/2);			// 当前点值占中点值比例，范围（0-200%），对应（0-2π）
		IQSinValue = _IQmpyI32int(2000, _IQsinPU(IQRatio));	// 点计数值公式：y1 = 2000 * sin(IQRatio * π)
		SinValueArray[N] = 2000 + IQSinValue;								// 将点计数值存入数组中：y2 = 2000 + y1
	}
	
	return SinValueArray;
}




