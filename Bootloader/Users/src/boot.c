#include "boot.h"


// BOOTLOADER��ת����
void Boot_Process() {
	
 	vu16 AppGotoFlag = Flash_Read(APP_GOTO_FLAG_START_ADDR);
	
	// ��AppGotoFlag����0ʱ����ʾ��ת��APP2��ΪȫF����1ʱ��ת��APP1
	Boot_GotoApp(AppGotoFlag!=0 ? APP1_START_ADDR : APP2_START_ADDR);
	while((*(vu32*)(APP1_START_ADDR+4)&0xF000000)!=0x8000000);
	Boot_GotoApp(APP1_START_ADDR);
}


// ��ת��ָ��APP
static void Boot_GotoApp(u32 AppStartAddr) {
	
	Goto_App App_Main = (Goto_App)*(vu32 *)(AppStartAddr + 4);
	
	MSR_MSP(*(vu32*)AppStartAddr);	// ����ջ����ַ
	
	__set_PRIMASK(1);   //�ر�STM32���ж�
	
	Delay_Ms(10);				// ��ʱ
	
	App_Main();					// ���뵽APP���ڵ�ϵͳ��λ������ʵ����ת��APP
}
