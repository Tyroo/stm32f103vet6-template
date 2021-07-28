#include "sys.h"

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
