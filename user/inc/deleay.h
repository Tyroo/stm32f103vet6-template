#ifndef __DELEAY_H__
#define __DELEAY_H__

/**
* @include
**/
#include "stm32f10x.h"



/**
* @function
* ���ã�ʵ�ֺ��뼶��ʱ
* ������{ ms: Ҫ��ʱ�ĺ����� }
* ����ֵ��void
**/
void Deleay_MS(int Ms);


/**
* @function
* ���ã�ʵ��΢�뼶��ʱ
* ������{ us: Ҫ��ʱ��΢���� }
* ����ֵ��void
**/
void Deleay_US(int Us);

#endif
