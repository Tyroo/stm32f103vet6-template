#ifndef __TIMER_H__
#define __TIMER_H__

/**
* @include
**/
#include "stm32f10x.h"


/**
* @variable
**/
extern u8 Timer2_Flag;


/**
* @function
* 作用：初始化定时器2，定时时间 = ((TimerCountValue + 1) * (PrescalerValue + 1)) * TimerClockDivision / 72000000
* 参数：{ 
*					TimerCountValue：定时器2计数值；
*					PrescalerValue：定时器2分频因子；
*					TimerClockDivision：定时器主时钟分频系数；
*				}
* 返回值：void
**/
void Timer2_Init(uint16_t TimerCountValue, uint16_t PrescalerValue, int TimerClockDivision);


/**
* @function
* 作用：初始化定时器3，定时时间 = ((TimerCountValue + 1) * (PrescalerValue + 1)) * TimerClockDivision / 72000000
* 参数：{ 
*					TimerCountValue：定时器3计数值；
*					PrescalerValue：定时器3分频因子；
*					TimerClockDivision：定时器主时钟分频系数；
*				}
* 返回值：void
**/
void Timer3_Init(uint16_t TimerCountValue, uint16_t PrescalerValue, int TimerClockDivision);


#endif
