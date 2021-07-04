/** ��ʱ��ģ�� **/
#include "timer.h"

// ͨ�ö�ʱ��2�жϺ���
void Timer2_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* �������ýṹ�� */
	TIM_TimeBaseInitTypeDef TIM_BaseInitStrucere;							 // ����һ����ʱ���������ýṹ��
	
	/* ʹ��ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			 // ʹ�ܶ�ʱ��2ʱ��
	
	/* ���ö�ʱ��2 */
	TIM_BaseInitStrucere.TIM_ClockDivision = 
	 (uint16_t)(128 * TimerClockDivision);		 								 // ���ö�ʱ����ʱ�ӵķ�Ƶϵ��
	TIM_BaseInitStrucere.TIM_CounterMode = TIM_CounterMode_Up; // ���ö�ʱ������ģʽ�����ϼ�����
	TIM_BaseInitStrucere.TIM_Period = PrescalerValue; 				 // ���ü���������ֵ
	TIM_BaseInitStrucere.TIM_Prescaler = PrescalerValue;			 // ���ö�ʱ���ķ�Ƶ����
	
	TIM_TimeBaseInit(TIM2, &TIM_BaseInitStrucere);						 // Ӧ��TIM2����
	
	TIM_Cmd(TIM2, ENABLE);																		 // ʹ��TIM2��ʱ��
	TIM_ITConfig(TIM2, TIM2_IRQn, ENABLE);										 // ʹ��TIM2��ʱ���ж�
	
}
	

// ��ʱ��2<�жϺ���>
void TIM2_IRQHandler() {
	// pass
}
