#include "stm32f10x.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"
#include "exti.h"
#include "timer.h"


int main() {
	
	/* ��ʼ��ģ������ */
	Nvic_Init(2);									// ��ʼ��NVICģ��
	Uart1_Init(115200);						// ��ʼ��UART1ģ��
	Led_Init();										// ��ʼ��LEDģ��
	Exti_Init();									// ��ʼ���ⲿ�ж�
	Timer3_Init(399, 3599, 1);	  // ��ʼ��TIM3ģ��(PWM)
	
	while (1) {
		
	}
}

