/** 定时器模块 **/
#include "timer.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"

// 通用定时器2中断函数
void Timer2_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* 定义配置结构体 */
	TIM_TimeBaseInitTypeDef TIM_InitStrucere;							 // 定义一个定时器基本配置结构体
	
	/* 使能时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 // 使能定时器2时钟
	
	/* 配置定时器2 */
	TIM_InitStrucere.TIM_ClockDivision =
		(uint16_t)(128 * (TimerClockDivision - 1));		 			 // 设置定时器主时钟的分频系数
	TIM_InitStrucere.TIM_CounterMode = TIM_CounterMode_Up; // 设置定时器计数模式（向上计数）
	TIM_InitStrucere.TIM_Period = TimerCountValue; 				 // 设置计数器计数值
	TIM_InitStrucere.TIM_Prescaler = PrescalerValue;			 // 设置定时器的分频因子
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStrucere);						 // 应用TIM2配置
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);						 // 允许TIM2定时器中断更新
		
	Nvic_Config(TIM2_IRQn, 0, 2, 1);											 // 配置TIM2中断优先级
		
	TIM_Cmd(TIM2, ENABLE);																 // 使能TIM2定时器
	
}
	

// 定时器2<中断函数>
void TIM2_IRQHandler() {
	
	ITStatus UpdateFlag = TIM_GetITStatus(TIM2, TIM_IT_Update);
	uint8_t  LedStatus = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7);
	
	if (UpdateFlag != RESET) {
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除TIM2更新中断标志
		Led_Set(~LedStatus);
		Uart1_Send("TIM2");
	
	}
}
