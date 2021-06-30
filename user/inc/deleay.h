#ifndef __DELEAY_H__
#define __DELEAY_H__

/**
* @include
**/
#include "stm32f10x.h"



/**
* @function
* 作用：实现毫秒级延时
* 参数：{ ms: 要延时的毫秒数 }
* 返回值：void
**/
void Deleay_MS(int Ms);


/**
* @function
* 作用：实现微秒级延时
* 参数：{ us: 要延时的微秒数 }
* 返回值：void
**/
void Deleay_US(int Us);

#endif
