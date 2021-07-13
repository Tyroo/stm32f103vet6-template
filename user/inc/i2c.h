#ifndef __I2C_H__
#define __I2C_H__


/**
* @include
**/
#include "gpio.h"
#include "delay.h"
#include "stm32f10x.h"



/**
*	@define
**/
// I2CΪ����ģʽ
#define I2C_Mode_Tx() {GPIOB->CRH &= ~(1<<12);GPIOB->CRH |= 8<<12;}
// I2CΪ����ģʽ
#define I2C_Mode_Rx() {GPIOB->CRH &= ~(1<<12);GPIOB->CRH |= 3<<12;}
// GPIOB����ӳ��IIC��
#define IIC_SCL     		PBout(10)	// IICʱ����
#define IIC_SDA_OUT     PBout(11)	// IIC���������
#define IIC_SDA_IN			PBin(11)	// IIC���ݶ�����

#endif
