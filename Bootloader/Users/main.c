#include "main.h"


int main() {
	
	/* ϵͳ��ʼ�� */
	Sys_Init();
	
	/* IAP�������� */
	Update_Process();
	
	/* BOOT��ת���� */
	Boot_Process();
	
	while (1);
}

