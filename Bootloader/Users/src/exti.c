/* 外部中断模块，管理所有的外部中断 */
#include "exti.h"
#include "nvic.h"
#include "uart.h"


// 所有外部中断的初始化函数
void Exti_Init() {
	
	// 将GPIOC4口映射为外部中断
	Gpio_Exti_Config(EXTI_Line4, EXTI_Trigger_Falling, 0, 1, 3, 4);
	// 配置GPIO4外部中断的优先级
	Nvic_Config(EXTI4_IRQn, 1, 1, 1);
	
}


// 配置GPIOC外部中断
void Gpio_Exti_Config(uint32_t Lin, EXTITrigger_TypeDef Trigger, int RequestMode, 
	int Enable, uint8_t GpioGroupNum, uint8_t GpioPinNum
) {
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);				// 使能GPIO端口复用时钟
	
	/* 定义配置结构体 */
	EXTI_InitTypeDef EXTI_InitStructre;													// 定义一个外部中断配置结构体
	GPIO_InitTypeDef GPIO_InitStructre;													// 定义一个GPIO中断配置结构体
	
	/* 配置GPIO */
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_IPD;								// 配置GPIO为下拉输入模式
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_4;										// 绑定GPIO4口
	
	GPIO_Init(GPIOC, &GPIO_InitStructre);												// 应用GPIOC4更改
	GPIO_EXTILineConfig(GpioGroupNum - 1, GpioPinNum);					// 将GPIOC4映射到外部中断线
	
	/* 配置外部中断 */
	EXTI_InitStructre.EXTI_Line = Lin;													// 设置中断线为4
	EXTI_InitStructre.EXTI_Trigger = Trigger;										// 设置路线为下降沿触发
	EXTI_InitStructre.EXTI_Mode = RequestMode? 
	 EXTI_Mode_Event : EXTI_Mode_Interrupt;									    // 设置线路为中断请求
	EXTI_InitStructre.EXTI_LineCmd = Enable? ENABLE : DISABLE;	// 使能该中断路线
	
	EXTI_Init(&EXTI_InitStructre);															// 应用Lin4的中断配置
	
}


// GPIOC4外部<中断函数>
void EXTI4_IRQHandler() {
	
	ITStatus LineStatus = EXTI_GetITStatus(EXTI_Line4);
	
	if (LineStatus != RESET) {
		Uart1_Send("Trigger GPIOC4 external interrupt!");						// 当触发此中断则向上位机发送消息
	}
	
	EXTI_ClearITPendingBit(EXTI_Line4);													  // 清除标志位
}
