/** ��ʱ��ģ�� **/
#include "timer.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"

// ͨ�ö�ʱ��2�жϺ���
void Timer2_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* �������ýṹ�� */
	TIM_TimeBaseInitTypeDef TIM_InitStrucere;							 // ����һ����ʱ���������ýṹ��
	
	/* ʹ��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 // ʹ�ܶ�ʱ��2ʱ��
	
	/* ���ö�ʱ��2 */
	TIM_InitStrucere.TIM_ClockDivision =
		(uint16_t)(128 * (TimerClockDivision - 1));		 			 // ���ö�ʱ����ʱ�ӵķ�Ƶϵ��
	TIM_InitStrucere.TIM_CounterMode = TIM_CounterMode_Up; // ���ö�ʱ������ģʽ�����ϼ�����
	TIM_InitStrucere.TIM_Period = TimerCountValue; 				 // ���ü���������ֵ
	TIM_InitStrucere.TIM_Prescaler = PrescalerValue;			 // ���ö�ʱ���ķ�Ƶ����
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStrucere);						 // Ӧ��TIM2����
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);						 // ����TIM2��ʱ���жϸ���
		
	Nvic_Config(TIM2_IRQn, 0, 2, 1);											 // ����TIM2�ж����ȼ�
		
	TIM_Cmd(TIM2, ENABLE);																 // ʹ��TIM2��ʱ��
	
}
	

// ��ͬ�ö�ʱ��3��ʼ��������PWM���
void Timer3_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* �������ýṹ�� */
	TIM_TimeBaseInitTypeDef TIM_InitStrucere;							 // ����һ����ʱ���������ýṹ��
	TIM_OCInitTypeDef				TIM_OCInitStructre;						 // ����һ��ͨ�����ýṹ��
	GPIO_InitTypeDef				GPIO_InitStruetre;						 //	����һ��GPIO���ýṹ��
	
	/* ʹ��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 // ʹ��TIM3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 // GPIOCʱ��ʹ��
	
	/* GPIO���� */
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);			 // ��TIM3��ȫ��ӳ��
	GPIO_InitStruetre.GPIO_Mode = GPIO_Mode_AF_PP;				 // ����IO������Ϊ�����������
	GPIO_InitStruetre.GPIO_Pin = GPIO_Pin_7;							 // ����Ϊ��7��IO��
	GPIO_InitStruetre.GPIO_Speed = GPIO_Speed_50MHz;			 // ��������ٶ�Ϊ50MHz
	
	/* TIM3���� */
	TIM_InitStrucere.TIM_Period = TimerCountValue;				 // ����TIM����װ��ֵ
	TIM_InitStrucere.TIM_Prescaler = PrescalerValue;			 // ����TIM�ķ�Ƶ����
	TIM_InitStrucere.TIM_ClockDivision = 
		(uint16_t)(128 * (TimerClockDivision - 1)); 				 // ���ö�ʱ����ʱ�ӵķ�Ƶϵ��
	TIM_InitStrucere.TIM_CounterMode = TIM_CounterMode_Up; // ���ö�ʱ������ģʽ�����ϼ�����
		
	/* ��ʱ��ͨ������ */
	TIM_OCInitStructre.TIM_OCMode = TIM_OCMode_PWM1;			 // ����Ϊͨ�����ģʽΪPWM1ģʽ
	TIM_OCInitStructre.TIM_OutputState = TIM_OutputState_Enable; // ����Ƚ�ʹ��
	TIM_OCInitStructre.TIM_OCPolarity = TIM_OCPolarity_Low;	// �������Ϊ��
	
	/* ��ʼ�� */
	TIM_TimeBaseInit(TIM3, &TIM_InitStrucere);						 // Ӧ��TIM3����
	GPIO_Init(GPIOA, &GPIO_InitStruetre);								   // Ӧ��GPIOC7����
	TIM_OC2Init(TIM3, &TIM_OCInitStructre);								 // Ӧ��ͨ������
	
	TIM_Cmd(TIM3, ENABLE);															   // ʹ��TIM3
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);						 // ����TIM3��ʱ���жϸ���
		
	Nvic_Config(TIM3_IRQn, 0, 2, 1);											 // ����TIM3�ж����ȼ�
	
}


// ��ʱ��2<�жϺ���>
void TIM2_IRQHandler() {
	
	ITStatus UpdateFlag = TIM_GetITStatus(TIM2, TIM_IT_Update);
	uint8_t  LedStatus = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7);
	
	if (UpdateFlag != RESET) {
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //���TIM2�����жϱ�־
		Led_Set(~LedStatus);
	
	}
}


// ��ʱ��3<�жϺ���>
void TIM3_IRQHandler() {
	
	static int PwmCount = 0;											// PWMռ�ձȼ�����
	static int PwmCountFlag = 0;									// PWMռ�ձȵ���/����־
	
	int PwmdutyChangePeriod = 200;								// PWMռ�ձȵ���/������
	
	ITStatus UpdateFlag = TIM_GetITStatus(TIM3, TIM_IT_Update);

	if (UpdateFlag != RESET) {
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //���TIM2�����жϱ�־
		
		if (PwmCount > PwmdutyChangePeriod - 1) 		// �������ﵽ��ֵ�����������ȴﵽ��ֵ������ʼ�ݼ�ʹ֮�䰵
			PwmCountFlag = 0;			
		
		if (PwmCount < 1) 	PwmCountFlag = 1;				// �������ﵽ��ֵ�����������ȴﵽ��ֵ������ʼ����ʹ֮����
		
		PwmCountFlag? PwmCount++ : PwmCount--;			// ���������PwmCountFlag������PwmCount
		
		TIM_SetCompare2(TIM3, PwmCount);						// ��ֵ���õ���Ӧ�Ĳ���ȽϼĴ�����
	}
}