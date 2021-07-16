#ifndef __WDG_H__
#define __WDG_H__

/**
* @include
**/
#include "stm32f10x.h"


/**
* @function
* 作用：IWDG（独立看门口）初始化函数
* 参数：{ 
*					PrescalerValue: IWDG时钟的分频系数（v=4*2^n，0<n<7）； 
*					ReloadValue：重装载值（0<v<0xff）；
*					IsEnable：是否使能（0/1）；
*				}
* 返回值：void
**/
void Iwdg_Init(int PrescalerValue, int ReloadValue, 
	int IsEnable);


/**
* @function
* 作用：IWDG喂狗函数
* 参数：void
* 返回值：void
**/
void Iwdg_Feed(void);


/**
* @function
* 作用：WWDG（窗口看门狗）初始化函数
* 参数：{
*					CountValue：递减计数器的计数值；
*					WinValue：窗口值，范围（0x40<v<CountValue）
*					PrescalerValue: WWDG分频系数（WWDG_Prescaler_1、WWDG_Prescaler_2、WWDG_Prescaler_4、WWDG_Prescaler_8）；
*					IsEnable：是否使能WWDG
*				}
* 返回值：void
**/
void Wwdg_Inti(int CountValue, uint8_t WinValue, 
	uint32_t PrescalerValue, int IsEnable);

#endif

