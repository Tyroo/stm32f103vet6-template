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

typedef enum {	True = 1, False = 0 } bool; // 类型重定义一个bool类型

/****************** @Function ******************/

/**
* 作用：对SPI1初始化
*	参数：void
*	返回值：void
**/
void Spi1_Init(void);

/**
* 作用：使用SPI1发送数据
* 参数：要发送的数据
*	返回值：True、False
**/
bool SPI1_Send(u8* SendData);

#endif
