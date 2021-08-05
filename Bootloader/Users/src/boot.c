#include "boot.h"

typedef void(*Goto_App)(void);


// BOOTLOADER��ת����
void Boot_Process() {
	
//	vu16 AppGotoFlag = Flash_Read(APP_GOTO_FLAG_START_ADDR);
//	
//	u8 AppGotoFlagTop = AppGotoFlag>>15;
	
//	u16 temp = 1;
	
	// ��App_Goto_Flag�����λΪ1��˵��оƬ��APP��תָʾλδд������ݣ���Ĭ����ת��APP1��
//	if(AppGotoFlagTop)
//		Flash_Write(APP_GOTO_FLAG_START_ADDR, &temp, 1);
//	else
//		Boot_GotoApp(AppGotoFlag==1 ? APP1_START_ADDR : APP2_START_ADDR);
	Boot_GotoApp(APP1_START_ADDR);
}


void Boot_GotoApp(u32 AppStartAddr) {
	
	Goto_App App_Main = (Goto_App)*(vu32 *)(AppStartAddr + 4);
	
	MSR_MSP(AppStartAddr);	// ����ջ����ַ
	
	__set_PRIMASK(1);    //�ر�STM32���ж�
	
	App_Main();					// ���뵽APP���ڵ�ϵͳ��λ������ʵ����ת��APP
}
