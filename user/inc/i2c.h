#ifndef __I2C_H__
#define __I2C_H__


/**
* @include
**/
#include <string.h>
#include "gpio.h"
#include "delay.h"
#include "stm32f10x.h"



/**
*	@define
**/
// I2C为发送模式
#define IIC_Mode_Tx() {GPIOB->CRH &= ~(1<<12);GPIOB->CRH |= 8<<12;}
// I2C为接收模式
#define IIC_Mode_Rx() {GPIOB->CRH &= ~(1<<12);GPIOB->CRH |= 3<<12;}
// GPIOB引脚映射IIC线
#define IIC_SCL     		PBout(10)	// IIC时钟线
#define IIC_SDA_OUT     PBout(11)	// IIC数据输出线
#define IIC_SDA_IN			PBin(11)	// IIC数据读入线
#define IIC_DATA_SIZE_MAX 32			// IIC接收数据最大长度（字节）


/**
*	@typedef
**/
typedef enum {	// 类型重定义，BOOL类型
	True = 1,
	False = 0,
} bool;

#endif
