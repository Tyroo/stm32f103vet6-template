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
	u32 START_ADDR;			// 规定Flash的起始地址
	u32 END_ADDR;				// 规定Flash的结束地址
	u16 PAGE_SIZE;	// Flash每页的容量，不同规格的芯片容量不同
} FLASH_CONFIG;


/**
* @function
* 作用：初始化Flash模块
* 参数：void
* 返回值：void
**/
void Flash_Init(void);
	

/**
* @function
* 作用：擦除Flash中一定页数的数据
* 参数：{ Addr: 起始地址；*Data：要写入的数据 }
* 返回值：void
**/
void Flash_Write(u32 Addr, u16 *Data);


/**
* @function
* 作用：擦除Flash中一定页数的数据
* 参数：{ StartPageAddr: 起始页起始地址；PageNum：要擦除的页数 }
* 返回值：void
**/
void Flash_Erase(u32 StartPageAddr, u16 PageNum);


/**
* @function
* 作用：擦除Flash中一定页数的数据
* 参数：{ *Addr：数据地址指针 }
* 返回值：void
**/
vu16 Flash_Read(u32 *Addr);



#endif
