#ifndef __LED_H__
#define __LED_H__


/**
* @include
**/
#include "stm32f10x.h"


/**
* @function
* ���ã�LEDС�Ƴ�ʼ��
* ������void
* ����ֵ��void
**/
void Led_Init(void);


/**
* @function
* ���ã�����LEDС��
* ������{ State: LED��״̬��1������0�ر� }
* ����ֵ��void
**/
void Led_Set(int State);
	

#endif
