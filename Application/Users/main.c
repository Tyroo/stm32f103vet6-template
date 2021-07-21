#include "stm32f10x.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"
#include "exti.h"
#include "timer.h"
#include "delay.h"
#include "dma.h"
#include "adc.h"


int main() {
	
	/* 初始化模块配置 */
	Nvic_Init(2);									// 初始化NVIC模块，中断分组2
	Led_Init();										// 初始化LED模块
	Uart1_Init(115200);						// 初始化UART1模块
	Exti_Init();									// 初始化外部中断
	Delay_Init();									// 初始化延时模块
	Timer2_Init(9999, 7199, 1);		// 初始化TIM2模块
	Adc1_Init();									// 初始化ADC1模块
	
	while(1) {
		
	}
}

