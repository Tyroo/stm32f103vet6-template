#ifndef __DAC_H__
#define __DAC_H__

/**
* @include
**/
#include "IQmathLib.h"
#include "stm32f10x.h"


/**
* @define
**/


/**
* @variable
**/
extern const u8 DAC_CNT_RESOLUTION; // DAC的计数值数组长度，个数越多分辨率越高，生成计数值数组速度越慢


/**
* @function
* 作用：初始化DAC模块
* 参数：void
* 返回值：void
**/
void Dac_Init(void);


/**
* @function
* 作用：生成以SampNum个点组成的sin曲线的离散数组
* 参数：void
* 返回值：sin曲线离散数组指针
**/
int* Dac_GenerCntArr_Sin(void);


#endif
