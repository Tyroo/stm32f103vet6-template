/* ADCģ�� (δ��֤)*/

#include "adc.h"
#include "nvic.h"


void Adc1_Init() {
	
	/* ���ýṹ�嶨�� */
	ADC_InitTypeDef ADC_InitStructre;											// ADC���ýṹ��
//	GPIO_InitTypeDef GPIO_InitStructre;										// GPIO���ýṹ��
	
	/* ʱ������ */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	// ʹ��ADCʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);											// ����ADC����Ƶ��
	
	/* ADC���� */
	ADC_InitStructre.ADC_Mode = ADC_Mode_Independent;			// ����ADC�Ĺ���ģʽΪ����ģʽ
	ADC_InitStructre.ADC_ScanConvMode = DISABLE;					// ����ADC�����ڷ�ɨ��ģʽ��
	ADC_InitStructre.ADC_ContinuousConvMode = DISABLE;		// ����ADCΪ���ι���ģʽ
	ADC_InitStructre.ADC_DataAlign = ADC_DataAlign_Right; // ���òɼ��������Ҷ���
	ADC_InitStructre.ADC_ExternalTrigConv = 
	 ADC_ExternalTrigConv_None;														// ����ADC��ת������Ϊ������������ⲿ������
	ADC_InitStructre.ADC_NbrOfChannel = 1;								// ���ù���ת��ͨ������ĿΪ1
	
	/* ��ʼ������ */
	ADC_Init(ADC1, &ADC_InitStructre);										// Ӧ��ADC1������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, 
	 ADC_SampleTime_239Cycles5);													// ����ADC1����ͨ��16���ڲ��¶ȴ��������ĵ�ת�����ȼ�Ϊ1�Ͳ���ʱ��
	
	/* ʹ��/ʧ�� */
	ADC_Cmd(ADC1,ENABLE);																	// ʹ��ADC1
	ADC_TempSensorVrefintCmd(ENABLE);											// ʹ��оƬ�ڲ��¶ȴ�����
//	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);								// ʹ��ADC1��ת�������ж�
//	
//	/* �ж����� */
//	Nvic_Config(ADC1_2_IRQn, 0, 0, 1);										// ����ADC�ж����ȼ���ʹ��
	
	/* ��λ/У׼ADC */
	ADC_ResetCalibration(ADC1);														// ����ADC1��У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1) == RESET);	// �ȴ�У׼�Ĵ����������
	
	ADC_StartCalibration(ADC1);														// ��ʼ��ADC1����У׼
	while(ADC_GetCalibrationStatus(ADC1) == RESET);				// �ȴ�У׼���
	
}


// ����ADCͨ����ת��
void Adc1_SetConvert(FunctionalState State) {

	ADC_SoftwareStartConvCmd(ADC1, State); 										// ���������������ADCת��
}


// ��ȡоƬ�ڲ��¶�
float Get_ChipTemperate(u8 ConvertNum) {
	
	float TemperateSum = 0;																		// �ɼ��¶ȵ��ܺͣ����ת��Ϊƽ���¶�

	// �ɼ�10�β�ȡƽ��ֵ
	for(u8 Index=0;Index<ConvertNum;Index++) {
		
		Adc1_SetConvert(ENABLE);																			// ����ADC1��ͨ��16��ת��
		
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	// �ȴ�ת�����
		
		TemperateSum += ADC_GetConversionValue(ADC1);						// ����ȡ��ת��ֵ����������
	}
	
	TemperateSum /= ConvertNum;
	TemperateSum *= (3.3/4096);
	TemperateSum = (1.43 - TemperateSum) / 0.0043 + 25;
	
	return TemperateSum;
}


// ADC1_2<�жϺ���>
void ADC1_2_IRQHandler() {
	
	u16 ConvertValue;																						// ת��ֵ
	FlagStatus ConvertFlag = ADC_GetITStatus(ADC1, ADC_IT_EOC);	// ת����ɱ�־
	
	// ��ת����ɺ����
	if (ConvertFlag != RESET) {
		ConvertValue = ADC_GetConversionValue(ADC1);							// ��ȡ����ͨ��ת����ֵ
	}
}



