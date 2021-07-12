#ifndef __I2C_H__
#define __I2C_H__


/**
* @include
**/
#include "stm32f10x.h"


/**
*	@define
**/
// I2C为发送模式
#define I2C_Mode_Tx() {GPIOB->CRH &= ~(1<<12);GPIOB->CRH |= 8<<12;}
// I2C为接收模式
#define I2C_Mode_Rx() {GPIOB->CRH &= ~(1<<12);GPIOB->CRH |= 3<<12;}
// 引脚/变量取别名
#define ANO_GPIO_I2C    GPIOB
#define I2C_Pin_SCL     GPIO_Pin_10
#define I2C_Pin_SDA     GPIO_Pin_11
#define ANO_RCC_I2C     RCC_APB2Periph_GPIOB
// SCL和SDA引脚的电平状态
#define SCL_H         ANO_GPIO_I2C->BSRR = I2C_Pin_SCL
#define SCL_L         ANO_GPIO_I2C->BRR  = I2C_Pin_SCL
#define SDA_H         ANO_GPIO_I2C->BSRR = I2C_Pin_SDA
#define SDA_L         ANO_GPIO_I2C->BRR  = I2C_Pin_SDA

#endif
