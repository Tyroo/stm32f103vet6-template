#include <stdio.h>
#include "stm32f10x.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"
#include "exti.h"
#include "timer.h"
#include "delay.h"
#include "dma.h"
#include "adc.h"
#include "dac.h"




int main() {
	
	/* �������� */
	uint8_t ADC1ChanneArray[1] = { 0x01 };
	
	/* ��ʼ��ģ������ */
	Nvic_Init(2);									// ��ʼ��NVICģ�飬�жϷ���2
	Led_Init();										// ��ʼ��LEDģ��
	Uart1_Init(115200);						// ��ʼ��UART1ģ��
	Exti_Init();									// ��ʼ���ⲿ�ж�
	Delay_Init();									// ��ʼ����ʱģ��
	Timer2_Init(9999, 7199, 1);		// ��ʼ��TIM2ģ��
	
	// ��ʼ��ADC1ͨ��16
	Adc1_Init(ENABLE, DISABLE, ADC1ChanneArray, 1);
	// ����ADC1��ͨ��16��ת��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);							
	Dac_Init();										// ��ʼ��DACģ��
	

//	float ChipTemperate = 0;
//	char ChipTemperateStr[] = "";
	
	int* Dac_CntArray = Dac_GenerCntArr_Sin();	// ����DAC����ֵ����
	
	while(1) {
		
//		if (Timer2_Flag&1) {
//			Timer2_Flag = 0;
//			ChipTemperate = Get_ChipTemperate(10);
//			sprintf(ChipTemperateStr, "Chip Temperate��%.2f��.\n", ChipTemperate);
//			Uart1_Send(ChipTemperateStr);
//		}
		
		for(u8 Index=0;Index<DAC_CNT_RESOLUTION;Index++) {
			Delay_Ms(10);
			DAC_SetChannel1Data(DAC_Channel_1, *(Dac_CntArray + Index));	// ����DAC����ֵ
		}
		
	}
}

