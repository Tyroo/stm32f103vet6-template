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
extern const u8 DAC_CNT_RESOLUTION; // DAC�ļ���ֵ���鳤�ȣ�����Խ��ֱ���Խ�ߣ����ɼ���ֵ�����ٶ�Խ��


/**
* @function
* ���ã���ʼ��DACģ��
* ������void
* ����ֵ��void
**/
void Dac_Init(void);


/**
* @function
* ���ã�������SampNum������ɵ�sin���ߵ���ɢ����
* ������void
* ����ֵ��sin������ɢ����ָ��
**/
int* Dac_GenerCntArr_Sin(void);


#endif
