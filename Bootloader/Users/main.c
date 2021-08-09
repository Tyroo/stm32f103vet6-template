#include "main.h"


int main() {
	
	/* 系统初始化 */
	Sys_Init();
	
	/* IAP升级处理 */
	Update_Process();
	
	/* BOOT跳转处理 */
	Boot_Process();
	
	while (1);
}

