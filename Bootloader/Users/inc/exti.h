#ifndef __EXTI_H__
#define __EXTI_H__


/**
* @include
**/
#include "stm32f10x.h"

/**
* @function
* 作用：所有外部中断初始化函数
* 参数：void
* 返回值：void
**/
void Exti_Init(void);


/**
* @function
* 作用：配置GPIO外部中断函数
* 参数：{ 
*					Lin：中断线名，如（EXTI_Line4）；
*					Trigger：触发方式，分为上升沿（EXTI_Trigger_Rising）、下降沿（EXTI_Trigger_Falling）、上升-下降沿（EXTI_Trigger_Falling）；
*					RequestMode：请求模式，分为中断模式（0），事件模式（1）；
*					Enable：使能（1），失能（0）；
*					GpioGroupNum：GPIO组号，A（1）、B（2）...、F（6）、G（7）；
*					GpioPinNum：GPIO口，与中断线名对应，（1、2、3、...）；
*				}
* 返回值：void
**/
void Gpio_Exti_Config(uint32_t Lin, EXTITrigger_TypeDef Trigger, 
	int RequestMode, int Enable, uint8_t GpioGroupNum, uint8_t GpioPinNum
);

#endif
