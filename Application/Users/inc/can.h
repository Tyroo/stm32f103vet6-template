#ifndef __CAN_H__
#define __CAN_H__


#include "stm32f10x_can.h"
#include "nvic.h"


void CAN1_Config(void);

unsigned char CAN1_Send_Msg(CanTxMsg* TxMsg);


#endif
