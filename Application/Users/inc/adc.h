#ifndef __ADC_H__

/****************** @Define ********************/

#define __ADC_H__

/****************** @Include *******************/

#include "stm32f10x.h"

/****************** @Variable ******************/



/****************** @Typedef *******************/



/****************** @Function ******************/

void Adc1_Init(void);

void Adc1_SetConvert(FunctionalState State);

float Get_ChipTemperate(u8 ConvertNum);


#endif

