#ifndef __UPDATE_H__
#define __UPDATE_H__

#include <stdio.h>
#include "flash.h"
#include "uart.h"
#include "timer.h"
#include "boot.h"

#define UPDATE_TIMEOUT 5


void Update_Process(void);

static void Update_CountDown(void);

#endif

