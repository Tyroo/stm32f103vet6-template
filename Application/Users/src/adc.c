/* ADC模块 (验证通过)*/
#include "adc.h"


// ADC1通道初始化
void Adc1_Init(FunctionalState IsConvMode, FunctionalState IsContinue, 
	uint8_t *ChannleArr, u8 ChannleArrLen) {
	
	/* 配置结构体定义 */
	ADC_InitTypeDef ADC_InitStructre;											// ADC配置结构体
	GPIO_InitTypeDef GPIO_InitStructre;									  // GPIO配置结构体
	
	/* 时钟配置 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);	// 使能ADC时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);											// 配置ADC采样频率
		
	/* GPIO配置 */
	GPIO_InitStructre.GPIO_Pin =GPIO_Pin_1;
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AIN;					//模拟输入
	GPIO_Init(GPIOA, &GPIO_InitStructre); 								//初始化 GPIOA1

	
	/* ADC配置 */
	ADC_InitStructre.ADC_Mode = ADC_Mode_Independent;			// 设置ADC的工作模式为独立模式
	ADC_InitStructre.ADC_ScanConvMode = IsConvMode;				// 设置ADC的扫描模式
	ADC_InitStructre.ADC_ContinuousConvMode = IsContinue;	// 设置ADC为单次工作模式
	ADC_InitStructre.ADC_DataAlign = ADC_DataAlign_Right; // 设置采集的数据右对齐
	ADC_InitStructre.ADC_ExternalTrigConv = 
	 ADC_ExternalTrigConv_None;														// 设置ADC的转换触发为软件触发（非外部触发）
	ADC_InitStructre.ADC_NbrOfChannel = ChannleArrLen;		// 设置规则转换通道的数目为1
		
	// 配置ADC1规则通道的转换优先级为和采样时间
	for (u8 CIndex=0;CIndex<ChannleArrLen;CIndex++) {
		ADC_RegularChannelConfig(ADC1, (uint8_t)(*(ChannleArr+CIndex)), CIndex+1, 
			ADC_SampleTime_239Cycles5);
	}

	/* 中断配置 */
	Nvic_Config(ADC1_2_IRQn, 0, 2, 1);										// 配置ADC中断优先级并使能
	
	/* 初始化配置 */
	ADC_Init(ADC1, &ADC_InitStructre);										// 应用ADC1的配置
	
	/* 使能/失能 */
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);								// 使能ADC1的转换结束中断
	ADC_Cmd(ADC1, ENABLE);																// 使能ADC1
	
	/* 复位/校准ADC */
	ADC_ResetCalibration(ADC1);														// 重设ADC1的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));						// 等待校准寄存器被设完成
	
	ADC_StartCalibration(ADC1);														// 开始对ADC1进行校准
	while(ADC_GetCalibrationStatus(ADC1));								// 等待校准完成
	
}


// 获取芯片内部温度
float Get_ChipTemperate(u8 ConvertNum) {
	
	float TemperateSum = 0;																		// 采集温度的总和，最后被转换为平稳温度

	ADC_TempSensorVrefintCmd(ENABLE);													// 使能芯片内部温度传感器
	
	// 采集10次并取平均值
	for(u8 Index=0;Index<ConvertNum;Index++) {
		
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);									// 开启ADC1的通道16的转换
		
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));					// 等待转换完成
		
		TemperateSum += ADC_GetConversionValue(ADC1);						// 将获取的转换值存入数组中
	}
	
	TemperateSum /= ConvertNum;																// 求出实际计数值
	TemperateSum *= (3.3/4096);																// 计数值转为电压值
	TemperateSum = (1.43 - TemperateSum) / 0.0043 + 25;				// 依据温度转换公式计算温度
	
	return TemperateSum;
}


// ADC1_2<中断函数>
void ADC1_2_IRQHandler() {
	
	float ConvertValue = 0;																		// 转换值
	static char ConvertValueStr[] = "";
	
	// 当转换完成后进入
	if (ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET) {
		
		ConvertValue = (ADC_GetConversionValue(ADC1) * 3.3) / 4096;							// 获取规则通道转换的值
		
		sprintf(ConvertValueStr, "Sin Value：%.2f\n", ConvertValue);
		Uart1_Send(ConvertValueStr);
		
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
	
	}
}
