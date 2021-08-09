#ifndef __UPDATE_H__
#define __UPDATE_H__

#include <stdio.h>
#include "flash.h"
#include "uart.h"
#include "timer.h"

#define UPDATE_FLAG_ADDR 0x8072000	// 0x8072000~0x80727FF

#define UPDATE_TIMEOUT 5


void Update_Process(void);

static void Update_CountDown(void);

#endif

