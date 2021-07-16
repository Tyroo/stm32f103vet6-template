#ifndef __FLASH_H__
#define __FLASH_H__

/**
* @include
**/
#include "stm32f10x.h"


/**
* @typedef
**/
typedef struct FLASH_CONFIG {
	u32 START_ADDR;			// �涨Flash����ʼ��ַ
	u32 END_ADDR;				// �涨Flash�Ľ�����ַ
	u16 PAGE_SIZE;	// Flashÿҳ����������ͬ����оƬ������ͬ
} FLASH_CONFIG;


/**
* @function
* ���ã���ʼ��Flashģ��
* ������void
* ����ֵ��void
**/
void Flash_Init(void);
	

/**
* @function
* ���ã�����Flash��һ��ҳ��������
* ������{ Addr: ��ʼ��ַ��*Data��Ҫд������� }
* ����ֵ��void
**/
void Flash_Write(u32 Addr, u16 *Data);


/**
* @function
* ���ã�����Flash��һ��ҳ��������
* ������{ StartPageAddr: ��ʼҳ��ʼ��ַ��PageNum��Ҫ������ҳ�� }
* ����ֵ��void
**/
void Flash_Erase(u32 StartPageAddr, u16 PageNum);


/**
* @function
* ���ã�����Flash��һ��ҳ��������
* ������{ *Addr�����ݵ�ַָ�� }
* ����ֵ��void
**/
vu16 Flash_Read(u32 *Addr);



#endif
