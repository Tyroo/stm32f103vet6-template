#include "stm32f10x.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"
#include "exti.h"


int main() {
	
	/* 初始化模块配置 */
	Nvic_Init(2);					// 初始化NVIC模块
	Uart1_Init(115200);		// 初始化UART1模块
	Led_Init();						// 初始化LED模块
	Exti_Init();					// 初始化外部中断
	
	int LedState = 1; 		// 定义LED的状态
	int TimeCount = 0;		// 定义一个时间计数器变量
	
	while (1) {
		
		TimeCount++;
		
		// 每计数5000000进入
		if (TimeCount>5000000) {
			
			TimeCount = 0;
			LedState = ~LedState;		// 反转LED灯状态
			Led_Set(LedState);			// 应用反转后的状态
			
		}
		
	}
}

