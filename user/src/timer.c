/** 定时器模块 **/
#include "timer.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"

// 通用定时器2中断函数
void Timer2_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* 定义配置结构体 */
	TIM_TimeBaseInitTypeDef TIM_InitStructre;							 // 定义一个定时器基本配置结构体
	
	/* 使能时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 // 使能定时器2时钟
	
	/* 配置定时器2 */
	TIM_InitStructre.TIM_ClockDivision =
		(uint16_t)(128 * (TimerClockDivision - 1));		 			 // 设置定时器主时钟的分频系数
	TIM_InitStructre.TIM_CounterMode = TIM_CounterMode_Up; // 设置定时器计数模式（向上计数）
	TIM_InitStructre.TIM_Period = TimerCountValue; 				 // 设置计数器计数值
	TIM_InitStructre.TIM_Prescaler = PrescalerValue;			 // 设置定时器的分频因子
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStructre);						 // 应用TIM2配置
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);						 // 允许TIM2定时器中断更新
		
	Nvic_Config(TIM2_IRQn, 0, 2, 1);											 // 配置TIM2中断优先级
		
	TIM_Cmd(TIM2, ENABLE);																 // 使能TIM2定时器
	
}
	

// 通用定时器3初始化，用作PWM输出
void Timer3_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* 定义配置结构体 */
	TIM_TimeBaseInitTypeDef TIM_InitStructre;							 // 定义一个定时器基本配置结构体
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
	TIM_InitStructre.TIM_Period = TimerCountValue;				 // 设置TIM的重装载值
	TIM_InitStructre.TIM_Prescaler = PrescalerValue;			 // 设置TIM的分频因子
	TIM_InitStructre.TIM_ClockDivision = 
		(uint16_t)(128 * (TimerClockDivision - 1)); 				 // 设置定时器主时钟的分频系数
	TIM_InitStructre.TIM_CounterMode = TIM_CounterMode_Up; // 设置定时器计数模式（向上计数）
		
	/* 定时器通道配置 */
	TIM_OCInitStructre.TIM_OCMode = TIM_OCMode_PWM1;			 // 配置为通道输出模式为PWM1模式
	TIM_OCInitStructre.TIM_OutputState = TIM_OutputState_Enable; // 输出比较使能
	TIM_OCInitStructre.TIM_OCPolarity = TIM_OCPolarity_Low;	// 输出极性为高
	
	/* 初始化 */
	TIM_TimeBaseInit(TIM3, &TIM_InitStructre);						 // 应用TIM3配置
	GPIO_Init(GPIOA, &GPIO_InitStruetre);								   // 应用GPIOC7配置
	TIM_OC2Init(TIM3, &TIM_OCInitStructre);								 // 应用通道配置
	
	TIM_Cmd(TIM3, ENABLE);															   // 使能TIM3
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);						 // 允许TIM3定时器中断更新
		
	Nvic_Config(TIM3_IRQn, 0, 2, 1);											 // 配置TIM3中断优先级
	
}
	

// 通用定时器5初始化，用作输入捕获
void Timer5_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
		
		/* 使能时钟 */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		// 使能TIM5时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// 使能GPIOA时钟
		
		/* 定义配置结构体 */
		TIM_TimeBaseInitTypeDef TIM_InitStructre;								// 定义定时器配置结构体
		TIM_ICInitTypeDef				TIM_ICInitStructre;							// 定义TIM输入捕获配置结构体
		
		/* 配置定时器5 */
		TIM_InitStructre.TIM_Period = TimerCountValue;					// 设置TIM的重装载值
		TIM_InitStructre.TIM_Prescaler = PrescalerValue;				// 设置TIM的分频因子
		TIM_InitStructre.TIM_ClockDivision = 
			(uint16_t)(128 * (TimerClockDivision - 1)); 					// 设置定时器主时钟的分频系数
		TIM_InitStructre.TIM_CounterMode = TIM_CounterMode_Up;	// 设置定时器计数模式（向上计数）
		
		/* 配置TIM5输入捕获 */
		TIM_ICInitStructre.TIM_Channel = TIM_Channel_1;				 					// 使用通道1来作为输入捕获
		TIM_ICInitStructre.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					// 设置输入分频
		TIM_ICInitStructre.TIM_ICPolarity = TIM_ICPolarity_Rising;			// 设置捕获上升沿信号
		TIM_ICInitStructre.TIM_ICSelection = TIM_ICSelection_DirectTI;	// 配置IC1直接映射在TI1上
		TIM_ICInitStructre.TIM_ICFilter = 0x00;													// 不使用输入滤波
		
		/* 初始化TIM5 */
		TIM_TimeBaseInit(TIM5, &TIM_InitStructre);						 					// 应用TIM5配置
		TIM_ICInit(TIM5, &TIM_ICInitStructre);													// 应用TIM5输入捕获配置
		
		TIM_ITConfig(TIM5, TIM_IT_Update|TIM_IT_CC1, ENABLE);						// 使能更新、捕获中断
		
		TIM_Cmd(TIM5, ENABLE);																					// 使能TIM5
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


// 定时器5<中断函数>
void TIM5_IRQHandler() {
	
	static int CaptureValue = 0;	// TIM5捕获的高电平计数值，可以定义为全局变量
	static int CaptureStatus = 0;	// 定义一个捕获状态变量，0：捕获到低电平，1：捕获到高电平，2：捕获超时
	
	ITStatus CaptureFlag = TIM_GetITStatus(TIM5, TIM_IT_CC1);	// 捕获标志位
	
	// 语句块1，当捕获到电平时或者捕获超时时进入
	if (CaptureFlag != RESET || CaptureStatus == 2) {
		
		if (CaptureStatus > 0) {
			
			CaptureStatus = 0;
			CaptureValue = TIM_GetCapture1(TIM5);								// 获取捕获的高电平计数值
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);	// 设置为上升沿捕获
			
		} else {
			
			CaptureStatus = 1;
			CaptureValue = 0;
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);	// 设置为下降沿捕获
			
		}
	// 语句块2，当没有捕获到电平时进入
	} else {	
		
		if (CaptureStatus == 1) CaptureValue++;	// 如果之前已经捕获了高电平，则开始高电平超出计数
		
		// 当高电平被捕获后，连续进入中断0x3f次还没有检测到低电平，则不再检测低电平，手动干预高电平计数值
		if (CaptureValue > 0x3f) {
			CaptureValue = 0;
			CaptureStatus = 2;		// 令捕获状态为捕获超时，在下次进入中断时运行语句块1，取得高电平计数值
		}
	}
	
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update|TIM_IT_CC1);	// 清除TIM5更新、捕获中断标志位
	
}
