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
	

// 如同用定时器3初始化，用作PWM输出
void Timer3_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* 定义配置结构体 */
	TIM_TimeBaseInitTypeDef TIM_InitStrucere;							 // 定义一个定时器基本配置结构体
	TIM_OCInitTypeDef				TIM_OCInitStructre;						 // 定义一个通道配置结构体
	GPIO_InitTypeDef				GPIO_InitStruetre;						 //	定义一个GPIO配置结构体
	
	/* 使能时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 // 使能TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 // GPIOC时钟使能
	
	/* GPIO配置 */
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);			 // 将TIM3完全重映射
	GPIO_InitStruetre.GPIO_Mode = GPIO_Mode_AF_PP;				 // 将该IO口设置为复用推挽输出
	GPIO_InitStruetre.GPIO_Pin = GPIO_Pin_7;							 // 设置为第7个IO口
	GPIO_InitStruetre.GPIO_Speed = GPIO_Speed_50MHz;			 // 设置输出速度为50MHz
	
	/* TIM3配置 */
	TIM_InitStrucere.TIM_Period = TimerCountValue;				 // 设置TIM的重装载值
	TIM_InitStrucere.TIM_Prescaler = PrescalerValue;			 // 设置TIM的分频因子
	TIM_InitStrucere.TIM_ClockDivision = 
		(uint16_t)(128 * (TimerClockDivision - 1)); 				 // 设置定时器主时钟的分频系数
	TIM_InitStrucere.TIM_CounterMode = TIM_CounterMode_Up; // 设置定时器计数模式（向上计数）
		
	/* 定时器通道配置 */
	TIM_OCInitStructre.TIM_OCMode = TIM_OCMode_PWM1;			 // 配置为通道输出模式为PWM1模式
	TIM_OCInitStructre.TIM_OutputState = TIM_OutputState_Enable; // 输出比较使能
	TIM_OCInitStructre.TIM_OCPolarity = TIM_OCPolarity_Low;	// 输出极性为高
	
	/* 初始化 */
	TIM_TimeBaseInit(TIM3, &TIM_InitStrucere);						 // 应用TIM3配置
	GPIO_Init(GPIOA, &GPIO_InitStruetre);								   // 应用GPIOC7配置
	TIM_OC2Init(TIM3, &TIM_OCInitStructre);								 // 应用通道配置
	
	TIM_Cmd(TIM3, ENABLE);															   // 使能TIM3
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);						 // 允许TIM3定时器中断更新
		
	Nvic_Config(TIM3_IRQn, 0, 2, 1);											 // 配置TIM3中断优先级
	
}


// 定时器2<中断函数>
void TIM2_IRQHandler() {
	
	ITStatus UpdateFlag = TIM_GetITStatus(TIM2, TIM_IT_Update);
	uint8_t  LedStatus = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7);
	
	if (UpdateFlag != RESET) {
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除TIM2更新中断标志
		Led_Set(~LedStatus);
	
	}
}


// 定时器3<中断函数>
void TIM3_IRQHandler() {
	
	static int PwmCount = 0;											// PWM占空比计数器
	static int PwmCountFlag = 0;									// PWM占空比递增/减标志
	
	int PwmdutyChangePeriod = 200;								// PWM占空比递增/减周期
	
	ITStatus UpdateFlag = TIM_GetITStatus(TIM3, TIM_IT_Update);

	if (UpdateFlag != RESET) {
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除TIM2更新中断标志
		
		if (PwmCount > PwmdutyChangePeriod - 1) 		// 当计数达到峰值（呼吸灯亮度达到峰值），则开始递减使之变暗
			PwmCountFlag = 0;			
		
		if (PwmCount < 1) 	PwmCountFlag = 1;				// 当计数达到谷值（呼吸灯亮度达到谷值），则开始递增使之变亮
		
		PwmCountFlag? PwmCount++ : PwmCount--;			// 依据上面的PwmCountFlag来控制PwmCount
		
		TIM_SetCompare2(TIM3, PwmCount);						// 将值设置到对应的捕获比较寄存器中
	}
}
