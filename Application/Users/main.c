#include "stm32f10x.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"
#include "exti.h"
#include "timer.h"
#include "delay.h"
#include "dma.h"
#include "adc.h"


int main() {
	
	/* ��ʼ��ģ������ */
	Nvic_Init(2);									// ��ʼ��NVICģ�飬�жϷ���2
	Led_Init();										// ��ʼ��LEDģ��
	Uart1_Init(115200);						// ��ʼ��UART1ģ��
	Exti_Init();									// ��ʼ���ⲿ�ж�
	Delay_Init();									// ��ʼ����ʱģ��
	Timer2_Init(9999, 7199, 1);		// ��ʼ��TIM2ģ��
	Adc1_Init();									// ��ʼ��ADC1ģ��
	
	while(1) {
		
	}
}

