#ifndef __WDG_H__
#define __WDG_H__

/**
* @include
**/
#include "stm32f10x.h"


/**
* @function
* ���ã�IWDG���������ſڣ���ʼ������
* ������{ 
*					PrescalerValue: IWDGʱ�ӵķ�Ƶϵ����v=4*2^n��0<n<7���� 
*					ReloadValue����װ��ֵ��0<v<0xff����
*					IsEnable���Ƿ�ʹ�ܣ�0/1����
*				}
* ����ֵ��void
**/
void Iwdg_Init(int PrescalerValue, int ReloadValue, 
	int IsEnable);


/**
* @function
* ���ã�IWDGι������
* ������void
* ����ֵ��void
**/
void Iwdg_Feed(void);


/**
* @function
* ���ã�WWDG�����ڿ��Ź�����ʼ������
* ������{
*					CountValue���ݼ��������ļ���ֵ��
*					WinValue������ֵ����Χ��0x40<v<CountValue��
*					PrescalerValue: WWDG��Ƶϵ����WWDG_Prescaler_1��WWDG_Prescaler_2��WWDG_Prescaler_4��WWDG_Prescaler_8����
*					IsEnable���Ƿ�ʹ��WWDG
*				}
* ����ֵ��void
**/
void Wwdg_Inti(int CountValue, uint8_t WinValue, 
	uint32_t PrescalerValue, int IsEnable);

#endif

