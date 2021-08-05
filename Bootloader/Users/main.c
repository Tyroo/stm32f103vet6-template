#include "main.h"

typedef void(*App_Fun_t)(void);

App_Fun_t app_main;


int main() {
	
	/* 系统初始化 */
	Sys_Init();
	
	/* IAP升级处理 */
	Update_Process();
	
//	/* BOOT跳转处理 */
//	Boot_Process();
	
	if(((*(vu32*)(0x08002000+4))&0xFF000000)==0x08000000){
		
		app_main = (App_Fun_t)*(vu32*)(0x08002004);
		/* 设置应用程序的堆栈 */
	  MSR_MSP(*(vu32*)(0x08002000));
		/* 跳转到应用程序执行 */
		Uart1_Send("Enter APP1");
		
		/* 关闭总中断 */
		__set_PRIMASK(1);
		
		Delay_Ms(10);
		
	  app_main();
	}else{
		Uart1_Send("Bootloader Error");
	}
	
	/* 防止程序跑飞 */
	while (1);
}

