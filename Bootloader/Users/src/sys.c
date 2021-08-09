#include "sys.h"


// ϵͳ��ʼ��
void Sys_Init() {
	
	Nvic_Init(2);									// ��ʼ��NVICģ�飬�жϷ���2
	Uart1_Init(115200);						// ��ʼ��UART1ģ��
	Flash_Init();									// ��ʼ��Flashģ��
	Led_Init();										// ��ʼ��LEDģ��
	Delay_Init();									// ��ʼ����ʱģ��
	Timer2_Init(9999, 7199, 1);		// ��ʼ��TIM2ģ��
	
	Led_Set(1);										// Bootloaderģʽ��LED����
}


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
