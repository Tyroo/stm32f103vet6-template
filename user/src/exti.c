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


// 配置GPIO外部中断
void Gpio_Exti_Config(uint32_t Lin, EXTITrigger_TypeDef Trigger, int RequestMode, 
	int Enable, uint8_t GpioGroupNum, uint8_t GpioPinNum
) {
	/* 定义配置结构体 */
	EXTI_InitTypeDef EXTI_InitStructre;													// 定义一个外部中断配置结构体
	
	/* 配置外部中断 */
	EXTI_InitStructre.EXTI_Line = Lin;													// 设置中断线为4
	EXTI_InitStructre.EXTI_Trigger = Trigger;										// 设置路线为上升-下降沿触发
	EXTI_InitStructre.EXTI_Mode = RequestMode? 
	 EXTI_Mode_Event : EXTI_Mode_Interrupt;									    // 设置线路为中断请求
	EXTI_InitStructre.EXTI_LineCmd = Enable? ENABLE : DISABLE;	// 使能该中断路线
	
	GPIO_EXTILineConfig(GpioGroupNum - 1, GpioPinNum);					// 将GPIOC4映射到外部中断线
	
	EXTI_Init(&EXTI_InitStructre);															// 应用Lin4的中断配置
	
}


void EXTI4_IRQHandler() {
	
	Uart1_Send("Trigger GPIOC4 external interrupt!");						// 当触发此中断则向上位机发送消息
	
}
