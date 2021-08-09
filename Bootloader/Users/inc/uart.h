#ifndef __UART_H__
#define __UART_H__


/**
* @include
**/
#include "stm32f10x.h"


/**
* @variable
**/
extern u16 UsartReceiveDataOne[100];
extern u16 UsartReceiveDataTwo[100];


extern u8 IsDownload;



/**
* @function
* 作用：初始化UART1
* 参数：{ Baud: UART的波特率 }
* 返回值：void
**/
void Uart1_Init(int Baud);


/**
* @function
* 作用：使用USART1发送数据
* 参数：{ Data: 要发送的数据指针 }
* 返回值：void
**/
void Uart1_Send(char *Data);



#endif
