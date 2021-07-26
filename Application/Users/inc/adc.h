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
* ���ã�ADC1ͨ��16��ʼ��
* ������void
* ����ֵ��void
**/
void Adc1_Init(FunctionalState IsConvMode, 
	FunctionalState IsContinue, uint8_t *ChannleArr, 
	u8 ChannleArrLen);


/**
* @function
* ���ã���ȡоƬ�ڲ��¶ȴ����������¶�
* ������{ ConvertNum����������������Խ��Խ׼���ٶ�Խ�� }
* ����ֵ��������оƬƽ���¶�
**/
float Get_ChipTemperate(u8 ConvertNum);


#endif

