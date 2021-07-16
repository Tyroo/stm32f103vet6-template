#ifndef __EXTI_H__
#define __EXTI_H__


/**
* @include
**/
#include "stm32f10x.h"

/**
* @function
* ���ã������ⲿ�жϳ�ʼ������
* ������void
* ����ֵ��void
**/
void Exti_Init(void);


/**
* @function
* ���ã�����GPIO�ⲿ�жϺ���
* ������{ 
*					Lin���ж��������磨EXTI_Line4����
*					Trigger��������ʽ����Ϊ�����أ�EXTI_Trigger_Rising�����½��أ�EXTI_Trigger_Falling��������-�½��أ�EXTI_Trigger_Falling����
*					RequestMode������ģʽ����Ϊ�ж�ģʽ��0�����¼�ģʽ��1����
*					Enable��ʹ�ܣ�1����ʧ�ܣ�0����
*					GpioGroupNum��GPIO��ţ�A��1����B��2��...��F��6����G��7����
*					GpioPinNum��GPIO�ڣ����ж�������Ӧ����1��2��3��...����
*				}
* ����ֵ��void
**/
void Gpio_Exti_Config(uint32_t Lin, EXTITrigger_TypeDef Trigger, 
	int RequestMode, int Enable, uint8_t GpioGroupNum, uint8_t GpioPinNum
);

#endif
