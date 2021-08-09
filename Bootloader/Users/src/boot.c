#include "boot.h"


// BOOTLOADER跳转处理
void Boot_Process() {
	
 	vu16 AppGotoFlag = Flash_Read(APP_GOTO_FLAG_START_ADDR);
	
	// 当AppGotoFlag被置0时，表示跳转到APP2，为全F或者1时跳转到APP1
	Boot_GotoApp(AppGotoFlag!=0 ? APP1_START_ADDR : APP2_START_ADDR);
	while((*(vu32*)(APP1_START_ADDR+4)&0xF000000)!=0x8000000);
	Boot_GotoApp(APP1_START_ADDR);
}


// 跳转至指定APP
static void Boot_GotoApp(u32 AppStartAddr) {
	
	Goto_App App_Main = (Goto_App)*(vu32 *)(AppStartAddr + 4);
	
	MSR_MSP(*(vu32*)AppStartAddr);	// 设置栈顶地址
	
	__set_PRIMASK(1);   //关闭STM32总中断
	
	Delay_Ms(10);				// 延时
	
	App_Main();					// 进入到APP所在的系统复位函数，实现跳转到APP
}
