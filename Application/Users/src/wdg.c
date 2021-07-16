/** 看门狗模块 **/
#include <math.h>
#include "wdg.h"

int CountValueMax = 0x7F;													// 定义一个递减计数器的最大值

// 独立看门狗初始化
void Iwdg_Init(int PrescalerValue, int ReloadValue, 
	int IsEnable) {
	
		IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	// 使能对寄存器IWDG_PR 和IWDG_RLR 的写操作
		IWDG_SetPrescaler(log2(PrescalerValue/4));		// 设置独立看门狗的预分频系数
		IWDG_SetReload(ReloadValue);									// 设置看门狗寄存器的重装载值
		IWDG_ReloadCounter();													// 装载设置的重装载值
		if (IsEnable&1) IWDG_Enable();								// 使能IWDG
}


// 窗口看门狗初始化
void Wwdg_Inti(int CountValue, uint8_t WinValue, 
	uint32_t PrescalerValue, int IsEnable) {
		
	CountValue &= CountValueMax;													// 用设置值&最大值，防止设置值超出最大值
	CountValueMax = CountValue;														// 将设置的值赋给外部最大值
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	// 开启WWDG时钟
	
	WWDG_SetPrescaler(PrescalerValue);										// 设置WWDG分频系数
	WWDG_SetWindowValue(WinValue);												// 设置窗口值
	WWDG_EnableIT();																			// 使能WWDG中断，使得计数值到在复位之前先触发WWDG中断

	if (IsEnable&1) {
		WWDG_Enable(CountValue);														// 设置计数器的值，并使能WWDG
	} else {
		WWDG_SetCounter(CountValue);												// 设置计数器值，但不使能
	}
	
}

	
// 独立看门狗喂狗函数
void Iwdg_Feed() {
	IWDG_ReloadCounter();														// 装载设置的重装载值
}


// WWDG中断函数
void WWDG_IRQHandler() {
	WWDG_SetCounter(CountValueMax);									// 重装载，防止系统复位
	WWDG_ClearFlag();																// 清除WWDG提前中断标志
}
