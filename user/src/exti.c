/* �ⲿ�ж�ģ�飬�������е��ⲿ�ж� */
#include "exti.h"
#include "nvic.h"
#include "uart.h"


// �����ⲿ�жϵĳ�ʼ������
void Exti_Init() {
	
	// ��GPIOC4��ӳ��Ϊ�ⲿ�ж�
	Gpio_Exti_Config(EXTI_Line4, EXTI_Trigger_Falling, 0, 1, 3, 4);
	// ����GPIO4�ⲿ�жϵ����ȼ�
	Nvic_Config(EXTI4_IRQn, 1, 1, 1);
	
}


// ����GPIO�ⲿ�ж�
void Gpio_Exti_Config(uint32_t Lin, EXTITrigger_TypeDef Trigger, int RequestMode, 
	int Enable, uint8_t GpioGroupNum, uint8_t GpioPinNum
) {
	/* �������ýṹ�� */
	EXTI_InitTypeDef EXTI_InitStructre;													// ����һ���ⲿ�ж����ýṹ��
	
	/* �����ⲿ�ж� */
	EXTI_InitStructre.EXTI_Line = Lin;													// �����ж���Ϊ4
	EXTI_InitStructre.EXTI_Trigger = Trigger;										// ����·��Ϊ����-�½��ش���
	EXTI_InitStructre.EXTI_Mode = RequestMode? 
	 EXTI_Mode_Event : EXTI_Mode_Interrupt;									    // ������·Ϊ�ж�����
	EXTI_InitStructre.EXTI_LineCmd = Enable? ENABLE : DISABLE;	// ʹ�ܸ��ж�·��
	
	GPIO_EXTILineConfig(GpioGroupNum - 1, GpioPinNum);					// ��GPIOC4ӳ�䵽�ⲿ�ж���
	
	EXTI_Init(&EXTI_InitStructre);															// Ӧ��Lin4���ж�����
	
}


void EXTI4_IRQHandler() {
	
	Uart1_Send("Trigger GPIOC4 external interrupt!");						// ���������ж�������λ��������Ϣ
	
}
