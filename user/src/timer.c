/** 定时器模块 **/
#include "timer.h"

// 通用定时器2中断函数
void Timer2_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* 定义配置结构体 */
	TIM_TimeBaseInitTypeDef TIM_BaseInitStrucere;							 // 定义一个定时器基本配置结构体
	
	/* 使能时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			 // 使能定时器2时钟
	
	/* 配置定时器2 */
	TIM_BaseInitStrucere.TIM_ClockDivision = 
	 (uint16_t)(128 * TimerClockDivision);		 								 // 设置定时器主时钟的分频系数
	TIM_BaseInitStrucere.TIM_CounterMode = TIM_CounterMode_Up; // 设置定时器计数模式（向上计数）
	TIM_BaseInitStrucere.TIM_Period = PrescalerValue; 				 // 设置计数器计数值
	TIM_BaseInitStrucere.TIM_Prescaler = PrescalerValue;			 // 设置定时器的分频因子
	
	TIM_TimeBaseInit(TIM2, &TIM_BaseInitStrucere);						 // 应用TIM2配置
	
	TIM_Cmd(TIM2, ENABLE);																		 // 使能TIM2定时器
	TIM_ITConfig(TIM2, TIM2_IRQn, ENABLE);										 // 使能TIM2定时器中断
	
}
	

// 定时器2<中断函数>
void TIM2_IRQHandler() {
	// pass
}
