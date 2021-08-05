#include "main.h"

typedef void(*App_Fun_t)(void);

App_Fun_t app_main;


int main() {
	
	/* ϵͳ��ʼ�� */
	Sys_Init();
	
	/* IAP�������� */
	Update_Process();
	
//	/* BOOT��ת���� */
//	Boot_Process();
	
	if(((*(vu32*)(0x08002000+4))&0xFF000000)==0x08000000){
		
		app_main = (App_Fun_t)*(vu32*)(0x08002004);
		/* ����Ӧ�ó���Ķ�ջ */
	  MSR_MSP(*(vu32*)(0x08002000));
		/* ��ת��Ӧ�ó���ִ�� */
		Uart1_Send("Enter APP1");
		
		/* �ر����ж� */
		__set_PRIMASK(1);
		
		Delay_Ms(10);
		
	  app_main();
	}else{
		Uart1_Send("Bootloader Error");
	}
	
	/* ��ֹ�����ܷ� */
	while (1);
}

