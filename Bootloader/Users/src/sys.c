#include "sys.h"

// ������ջ��ַ������Ϊջ����ַ
__asm void MSR_MSP(u32 addr) {
    MSR MSP, r0 			
    BX r14
}


// ϵͳ�����λ
void Sys_SoftReset(void) {
    __set_FAULTMASK(1); // �ر������ж�
    NVIC_SystemReset(); // ��λ
}
