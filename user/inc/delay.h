#ifndef __DELAY_H__
#define __DELAY_H__

/**
*	@include
**/
#include "stm32f10x.h"


/**
*	@define
**/
#define DELAY_ONE_US 9									// ��ʱ1us����ֵ
#define DELAY_ONE_MS (DELAY_ONE_US * 1000) 	// ��ʱ1ms����ֵ


/**
* @function
*	���ã���ʱģ���ʼ������
*	������void
*	����ֵ��void
**/
void Delay_Init(void);


/**
* @function
*	���ã�ʵ��΢�뼶��ʱ
*	������{ Us��Ҫ��ʱ��΢���� }
*	����ֵ��void
**/
void Delay_Us(u16 Us);


/**
* @function
*	���ã�ʵ�ֺ��뼶��ʱ
*	������{ Ms��Ҫ��ʱ�ĺ����� }
*	����ֵ��void
**/
void Delay_Ms(u16 Ms);

#endif