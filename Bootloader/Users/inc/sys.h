#ifndef __SYS_H__
#define __SYS_H__

/**
* @include
**/
#include "stm32f10x.h"


/**
* @typedef
**/
typedef void (*Goto_App)(void);


/**
* @function
**/
void MSR_MSP(u32 addr);

void Sys_SoftReset(void);


#endif
