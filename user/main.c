#include "stm32f10x.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"
#include "exti.h"


int main() {
	
	/* ��ʼ��ģ������ */
	Nvic_Init(2);					// ��ʼ��NVICģ��
	Uart1_Init(115200);		// ��ʼ��UART1ģ��
	Led_Init();						// ��ʼ��LEDģ��
	Exti_Init();					// ��ʼ���ⲿ�ж�
	
	int LedState = 1; 		// ����LED��״̬
	int TimeCount = 0;		// ����һ��ʱ�����������
	
	while (1) {
		
		TimeCount++;
		
		// ÿ����5000000����
		if (TimeCount>5000000) {
			
			TimeCount = 0;
			LedState = ~LedState;		// ��תLED��״̬
			Led_Set(LedState);			// Ӧ�÷�ת���״̬
			
		}
		
	}
}

