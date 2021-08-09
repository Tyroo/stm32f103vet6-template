#include "sys.h"


// 系统初始化
void Sys_Init() {
	
	Nvic_Init(2);									// 初始化NVIC模块，中断分组2
	Uart1_Init(115200);						// 初始化UART1模块
	Flash_Init();									// 初始化Flash模块
	Led_Init();										// 初始化LED模块
	Delay_Init();									// 初始化延时模块
	Timer2_Init(9999, 7199, 1);		// 初始化TIM2模块
	
	Led_Set(1);										// Bootloader模式下LED常亮
}


// 设置主栈地址，参数为栈顶地址
__asm void MSR_MSP(u32 addr) {
    MSR MSP, r0 			
    BX r14
}


// 系统软件复位
void Sys_SoftReset(void) {
    __set_FAULTMASK(1); // 关闭所有中断
    NVIC_SystemReset(); // 复位
}
