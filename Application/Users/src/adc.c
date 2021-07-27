/* ADCģ�� (��֤ͨ��)*/
#include "adc.h"


// ADC1ͨ����ʼ��
void Adc1_Init(FunctionalState IsConvMode, FunctionalState IsContinue, 
	uint8_t *ChannleArr, u8 ChannleArrLen) {
	
	/* ���ýṹ�嶨�� */
	ADC_InitTypeDef ADC_InitStructre;											// ADC���ýṹ��
	GPIO_InitTypeDef GPIO_InitStructre;									  // GPIO���ýṹ��
	
	/* ʱ������ */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);	// ʹ��ADCʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);											// ����ADC����Ƶ��
		
	/* GPIO���� */
	GPIO_InitStructre.GPIO_Pin =GPIO_Pin_1;
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_AIN;					//ģ������
	GPIO_Init(GPIOA, &GPIO_InitStructre); 								//��ʼ�� GPIOA1

	
	/* ADC���� */
	ADC_InitStructre.ADC_Mode = ADC_Mode_Independent;			// ����ADC�Ĺ���ģʽΪ����ģʽ
	ADC_InitStructre.ADC_ScanConvMode = IsConvMode;				// ����ADC��ɨ��ģʽ
	ADC_InitStructre.ADC_ContinuousConvMode = IsContinue;	// ����ADCΪ���ι���ģʽ
	ADC_InitStructre.ADC_DataAlign = ADC_DataAlign_Right; // ���òɼ��������Ҷ���
	ADC_InitStructre.ADC_ExternalTrigConv = 
	 ADC_ExternalTrigConv_None;														// ����ADC��ת������Ϊ������������ⲿ������
	ADC_InitStructre.ADC_NbrOfChannel = ChannleArrLen;		// ���ù���ת��ͨ������ĿΪ1
		
	// ����ADC1����ͨ����ת�����ȼ�Ϊ�Ͳ���ʱ��
	for (u8 CIndex=0;CIndex<ChannleArrLen;CIndex++) {
		ADC_RegularChannelConfig(ADC1, (uint8_t)(*(ChannleArr+CIndex)), CIndex+1, 
			ADC_SampleTime_239Cycles5);
	}

	/* �ж����� */
	Nvic_Config(ADC1_2_IRQn, 0, 2, 1);										// ����ADC�ж����ȼ���ʹ��
	
	/* ��ʼ������ */
	ADC_Init(ADC1, &ADC_InitStructre);										// Ӧ��ADC1������
	
	/* ʹ��/ʧ�� */
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);								// ʹ��ADC1��ת�������ж�
	ADC_Cmd(ADC1, ENABLE);																// ʹ��ADC1
	
	/* ��λ/У׼ADC */
	ADC_ResetCalibration(ADC1);														// ����ADC1��У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));						// �ȴ�У׼�Ĵ����������
	
	ADC_StartCalibration(ADC1);														// ��ʼ��ADC1����У׼
	while(ADC_GetCalibrationStatus(ADC1));								// �ȴ�У׼���
	
}


// ��ȡоƬ�ڲ��¶�
float Get_ChipTemperate(u8 ConvertNum) {
	
	float TemperateSum = 0;																		// �ɼ��¶ȵ��ܺͣ����ת��Ϊƽ���¶�

	ADC_TempSensorVrefintCmd(ENABLE);													// ʹ��оƬ�ڲ��¶ȴ�����
	
	// �ɼ�10�β�ȡƽ��ֵ
	for(u8 Index=0;Index<ConvertNum;Index++) {
		
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);									// ����ADC1��ͨ��16��ת��
		
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));					// �ȴ�ת�����
		
		TemperateSum += ADC_GetConversionValue(ADC1);						// ����ȡ��ת��ֵ����������
	}
	
	TemperateSum /= ConvertNum;																// ���ʵ�ʼ���ֵ
	TemperateSum *= (3.3/4096);																// ����ֵתΪ��ѹֵ
	TemperateSum = (1.43 - TemperateSum) / 0.0043 + 25;				// �����¶�ת����ʽ�����¶�
	
	return TemperateSum;
}


// ADC1_2<�жϺ���>
void ADC1_2_IRQHandler() {
	
	float ConvertValue = 0;																		// ת��ֵ
	static char ConvertValueStr[] = "";
	
	// ��ת����ɺ����
	if (ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET) {
		
		ConvertValue = (ADC_GetConversionValue(ADC1) * 3.3) / 4096;							// ��ȡ����ͨ��ת����ֵ
		
		sprintf(ConvertValueStr, "Sin Value��%.2f\n", ConvertValue);
		Uart1_Send(ConvertValueStr);
		
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
	
	}
}
