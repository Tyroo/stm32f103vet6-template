#ifndef __SPI_H__

/****************** @Define ********************/

#define __SPI_H__

/****************** @Include *******************/

#include "stm32f10x.h"
#include "uart.h"
#include "nvic.h"

/****************** @Variable ******************/

extern u8 SpiReceiveData[50];

/****************** @Typedef *******************/

typedef enum {	True = 1, False = 0 } bool; // �����ض���һ��bool����

/****************** @Function ******************/

/**
* ���ã���SPI1��ʼ��
*	������void
*	����ֵ��void
**/
void Spi1_Init(void);

/**
* ���ã�ʹ��SPI1��������
* ������Ҫ���͵�����
*	����ֵ��True��False
**/
bool SPI1_Send(u8* SendData);

#endif
