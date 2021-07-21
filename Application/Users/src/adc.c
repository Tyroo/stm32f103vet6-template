/* ADC模块 (未验证)*/

#include "adc.h"
#include "nvic.h"


void Adc1_Init() {
	
	/* 配置结构体定义 */
	ADC_InitTypeDef ADC_InitStructre;											// ADC配置结构体
//	GPIO_InitTypeDef GPIO_InitStructre;										// GPIO配置结构体
	
	/* 时钟配置 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	// 使能ADC时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);											// 配置ADC采样频率
	
	/* ADC配置 */
	ADC_InitStructre.ADC_Mode = ADC_Mode_Independent;			// 设置ADC的工作模式为独立模式
	ADC_InitStructre.ADC_ScanConvMode = DISABLE;					// 设置ADC工作在非扫描模式下
	ADC_InitStructre.ADC_ContinuousConvMode = DISABLE;		// 设置ADC为单次工作模式
	ADC_InitStructre.ADC_DataAlign = ADC_DataAlign_Right; // 设置采集的数据右对齐
	ADC_InitStructre.ADC_ExternalTrigConv = 
	 ADC_ExternalTrigConv_None;														// 设置ADC的转换触发为软件触发（非外部触发）
	ADC_InitStructre.ADC_NbrOfChannel = 1;								// 设置规则转换通道的数目为1
	
	/* 初始化配置 */
	ADC_Init(ADC1, &ADC_InitStructre);										// 应用ADC1的配置
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, 
	 ADC_SampleTime_239Cycles5);													// 配置ADC1规则通道16（内部温度传感器）的的转换优先级为1和采样时间
	
	/* 使能/失能 */
	ADC_Cmd(ADC1,ENABLE);																	// 使能ADC1
	ADC_TempSensorVrefintCmd(ENABLE);											// 使能芯片内部温度传感器
//	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);								// 使能ADC1的转换结束中断
//	
//	/* 中断配置 */
//	Nvic_Config(ADC1_2_IRQn, 0, 0, 1);										// 配置ADC中断优先级并使能
	
	/* 复位/校准ADC */
	ADC_ResetCalibration(ADC1);														// 重设ADC1的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1) == RESET);	// 等待校准寄存器被设完成
	
	ADC_StartCalibration(ADC1);														// 开始对ADC1进行校准
	while(ADC_GetCalibrationStatus(ADC1) == RESET);				// 等待校准完成
	
}


// 开启ADC通道的转换
void Adc1_SetConvert(FunctionalState State) {

	ADC_SoftwareStartConvCmd(ADC1, State); 										// 开启由软件触发的ADC转换
}


// 获取芯片内部温度
float Get_ChipTemperate(u8 ConvertNum) {
	
	float TemperateSum = 0;																		// 采集温度的总和，最后被转换为平稳温度

	// 采集10次并取平均值
	for(u8 Index=0;Index<ConvertNum;Index++) {
		
		Adc1_SetConvert(ENABLE);																			// 开启ADC1的通道16的转换
		
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	// 等待转换完成
		
		TemperateSum += ADC_GetConversionValue(ADC1);						// 将获取的转换值存入数组中
	}
	
	TemperateSum /= ConvertNum;
	TemperateSum *= (3.3/4096);
	TemperateSum = (1.43 - TemperateSum) / 0.0043 + 25;
	
	return TemperateSum;
}


// ADC1_2<中断函数>
void ADC1_2_IRQHandler() {
	
	u16 ConvertValue;																						// 转换值
	FlagStatus ConvertFlag = ADC_GetITStatus(ADC1, ADC_IT_EOC);	// 转换完成标志
	
	// 当转换完成后进入
	if (ConvertFlag != RESET) {
		ConvertValue = ADC_GetConversionValue(ADC1);							// 获取规则通道转换的值
	}
}



