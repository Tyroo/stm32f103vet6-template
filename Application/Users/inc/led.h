#ifndef __LED_H__
#define __LED_H__


/**
* @include
**/
#include "stm32f10x.h"


/**
* @function
* 作用：LED小灯初始化
* 参数：void
* 返回值：void
**/
void Led_Init(void);


/**
* @function
* 作用：开启LED小灯
* 参数：{ State: LED的状态，1开启，0关闭 }
* 返回值：void
**/
void Led_Set(int State);
	

#endif
