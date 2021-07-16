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


// ����GPIOC�ⲿ�ж�
void Gpio_Exti_Config(uint32_t Lin, EXTITrigger_TypeDef Trigger, int RequestMode, 
	int Enable, uint8_t GpioGroupNum, uint8_t GpioPinNum
) {
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);				// ʹ��GPIO�˿ڸ���ʱ��
	
	/* �������ýṹ�� */
	EXTI_InitTypeDef EXTI_InitStructre;													// ����һ���ⲿ�ж����ýṹ��
	GPIO_InitTypeDef GPIO_InitStructre;													// ����һ��GPIO�ж����ýṹ��
	
	/* ����GPIO */
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_IPD;								// ����GPIOΪ��������ģʽ
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_4;										// ��GPIO4��
	
	GPIO_Init(GPIOC, &GPIO_InitStructre);												// Ӧ��GPIOC4����
	GPIO_EXTILineConfig(GpioGroupNum - 1, GpioPinNum);					// ��GPIOC4ӳ�䵽�ⲿ�ж���
	
	/* �����ⲿ�ж� */
	EXTI_InitStructre.EXTI_Line = Lin;													// �����ж���Ϊ4
	EXTI_InitStructre.EXTI_Trigger = Trigger;										// ����·��Ϊ�½��ش���
	EXTI_InitStructre.EXTI_Mode = RequestMode? 
	 EXTI_Mode_Event : EXTI_Mode_Interrupt;									    // ������·Ϊ�ж�����
	EXTI_InitStructre.EXTI_LineCmd = Enable? ENABLE : DISABLE;	// ʹ�ܸ��ж�·��
	
	EXTI_Init(&EXTI_InitStructre);															// Ӧ��Lin4���ж�����
	
}


// GPIOC4�ⲿ<�жϺ���>
void EXTI4_IRQHandler() {
	
	ITStatus LineStatus = EXTI_GetITStatus(EXTI_Line4);
	
	if (LineStatus != RESET) {
		Uart1_Send("Trigger GPIOC4 external interrupt!");						// ���������ж�������λ��������Ϣ
	}
	
	EXTI_ClearITPendingBit(EXTI_Line4);													  // �����־λ
}
