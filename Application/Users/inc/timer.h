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
* ���ã���ʼ����ʱ��2����ʱʱ�� = ((TimerCountValue + 1) * (PrescalerValue + 1)) * TimerClockDivision / 72000000
* ������{ 
*					TimerCountValue����ʱ��2����ֵ��
*					PrescalerValue����ʱ��2��Ƶ���ӣ�
*					TimerClockDivision����ʱ����ʱ�ӷ�Ƶϵ����
*				}
* ����ֵ��void
**/
void Timer2_Init(uint16_t TimerCountValue, uint16_t PrescalerValue, int TimerClockDivision);


/**
* @function
* ���ã���ʼ����ʱ��3����ʱʱ�� = ((TimerCountValue + 1) * (PrescalerValue + 1)) * TimerClockDivision / 72000000
* ������{ 
*					TimerCountValue����ʱ��3����ֵ��
*					PrescalerValue����ʱ��3��Ƶ���ӣ�
*					TimerClockDivision����ʱ����ʱ�ӷ�Ƶϵ����
*				}
* ����ֵ��void
**/
void Timer3_Init(uint16_t TimerCountValue, uint16_t PrescalerValue, int TimerClockDivision);


#endif
