#ifndef __ADC_H__

/****************** @Define ********************/

#define __ADC_H__

/****************** @Include *******************/

#include <stdio.h>
#include "stm32f10x.h"
#include "nvic.h"
#include "uart.h"

/****************** @Variable ******************/



/****************** @Typedef *******************/



/****************** @Function ******************/

/**
* @function
* 作用：ADC1通道16初始化
* 参数：void
* 返回值：void
**/
void Adc1_Init(FunctionalState IsConvMode, 
	FunctionalState IsContinue, uint8_t *ChannleArr, 
	u8 ChannleArrLen);


/**
* @function
* 作用：获取芯片内部温度传感器检测的温度
* 参数：{ ConvertNum：采样次数，次数越多越准，速度越慢 }
* 返回值：计算后的芯片平均温度
**/
float Get_ChipTemperate(u8 ConvertNum);


#endif

