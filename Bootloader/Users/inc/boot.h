#ifndef __BOOT_H__
#define __BOOT_H__


#include <stdio.h>
#include "sys.h"
#include "flash.h"
#include "stm32f10x.h"


/*************************************************************************************************************
*								*					 				*					*                    *
*		   BootLoader	        *               APP1	 		    *        APP2   	*       Parameter	 *
*								*					 				*					*                    *
**************************************************************************************************************
*								*					 				*					*                    *
*		   0x8000000	        *		       0x8002000	 	    *	   0x803A000    *		0x8072000	 *
*			   |				*				   |                *		   |		*			|		 *
*		   0x8001FFF		    *		       0x8039FFF		    *	   0x8071FFF	*		0x807FFFF	 *
*								*					 				*					*                    *
**************************************************************************************************************/

/* Flash各个存储区的首地址 */
#define BOOT_START_ADDR      (u32)0x8000000
#define APP1_START_ADDR      (u32)0x8002000
#define APP2_START_ADDR      (u32)0x803A000
#define PARAM_START_ADDR     (u32)0x8072000


/* Flash各个存储区的容量，单位（KB） */
#define BOOT_CAPACITY 8
#define APP1_CAPACITY 224
#define APP2_CAPACITY 224
#define PARAM_CAPACITY 56


/* 参数区个参数首地址 */

// APP跳转标志首地址，指示跳转到APP1还是APP2
#define APP_GOTO_FLAG_START_ADDR (u32)0x8072800		//（0x8072800~0x8072FFF）
// APP更新标志首地址，指示APP是否要更新
#define UPDATE_FLAG_ADDR 0x8072000					//（0x8072000~0x80727FF）



/**
* @typedef
**/
typedef void (*Goto_App)(void);

void Boot_Process(void);

static void Boot_GotoApp(u32 AppStartAddr);

#endif
