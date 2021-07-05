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
	

// ��ʱ��2<�жϺ���>
void TIM2_IRQHandler() {
	
	ITStatus UpdateFlag = TIM_GetITStatus(TIM2, TIM_IT_Update);
	uint8_t  LedStatus = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7);
	
	if (UpdateFlag != RESET) {
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //���TIM2�����жϱ�־
		Led_Set(~LedStatus);
		Uart1_Send("TIM2");
	
	}
}
