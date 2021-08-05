#ifndef __SYS_H__
#define __SYS_H__

/**
* @include
**/
#include "stm32f10x.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"
#include "exti.h"
#include "timer.h"
#include "delay.h"


/**
* @typedef
**/




/**
* @function
**/
void Sys_Init(void);

void MSR_MSP(u32 addr);

void Sys_SoftReset(void);


#endif
