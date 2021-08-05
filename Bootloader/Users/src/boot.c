#include "boot.h"

typedef void(*Goto_App)(void);


// BOOTLOADER跳转处理
void Boot_Process() {
	
//	vu16 AppGotoFlag = Flash_Read(APP_GOTO_FLAG_START_ADDR);
//	
//	u8 AppGotoFlagTop = AppGotoFlag>>15;
	
//	u16 temp = 1;
	
	// 若App_Goto_Flag的最高位为1则说明芯片的APP跳转指示位未写入过数据，则默认跳转到APP1中
//	if(AppGotoFlagTop)
//		Flash_Write(APP_GOTO_FLAG_START_ADDR, &temp, 1);
//	else
//		Boot_GotoApp(AppGotoFlag==1 ? APP1_START_ADDR : APP2_START_ADDR);
	Boot_GotoApp(APP1_START_ADDR);
}


void Boot_GotoApp(u32 AppStartAddr) {
	
	Goto_App App_Main = (Goto_App)*(vu32 *)(AppStartAddr + 4);
	
	MSR_MSP(AppStartAddr);	// 设置栈顶地址
	
	__set_PRIMASK(1);    //关闭STM32总中断
	
	App_Main();					// 进入到APP所在的系统复位函数，实现跳转到APP
}
