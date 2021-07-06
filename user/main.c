#include "stm32f10x.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"
#include "exti.h"
#include "timer.h"


int main() {
	
	/* 初始化模块配置 */
	Nvic_Init(2);									// 初始化NVIC模块
	Uart1_Init(115200);						// 初始化UART1模块
	Led_Init();										// 初始化LED模块
	Exti_Init();									// 初始化外部中断
	Timer3_Init(399, 3599, 1);	  // 初始化TIM3模块(PWM)
	
	while (1) {
		
	}
}

