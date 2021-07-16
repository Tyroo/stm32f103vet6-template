/** ���Ź�ģ�� **/
#include <math.h>
#include "wdg.h"

int CountValueMax = 0x7F;													// ����һ���ݼ������������ֵ

// �������Ź���ʼ��
void Iwdg_Init(int PrescalerValue, int ReloadValue, 
	int IsEnable) {
	
		IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	// ʹ�ܶԼĴ���IWDG_PR ��IWDG_RLR ��д����
		IWDG_SetPrescaler(log2(PrescalerValue/4));		// ���ö������Ź���Ԥ��Ƶϵ��
		IWDG_SetReload(ReloadValue);									// ���ÿ��Ź��Ĵ�������װ��ֵ
		IWDG_ReloadCounter();													// װ�����õ���װ��ֵ
		if (IsEnable&1) IWDG_Enable();								// ʹ��IWDG
}


// ���ڿ��Ź���ʼ��
void Wwdg_Inti(int CountValue, uint8_t WinValue, 
	uint32_t PrescalerValue, int IsEnable) {
		
	CountValue &= CountValueMax;													// ������ֵ&���ֵ����ֹ����ֵ�������ֵ
	CountValueMax = CountValue;														// �����õ�ֵ�����ⲿ���ֵ
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	// ����WWDGʱ��
	
	WWDG_SetPrescaler(PrescalerValue);										// ����WWDG��Ƶϵ��
	WWDG_SetWindowValue(WinValue);												// ���ô���ֵ
	WWDG_EnableIT();																			// ʹ��WWDG�жϣ�ʹ�ü���ֵ���ڸ�λ֮ǰ�ȴ���WWDG�ж�

	if (IsEnable&1) {
		WWDG_Enable(CountValue);														// ���ü�������ֵ����ʹ��WWDG
	} else {
		WWDG_SetCounter(CountValue);												// ���ü�����ֵ������ʹ��
	}
	
}

	
// �������Ź�ι������
void Iwdg_Feed() {
	IWDG_ReloadCounter();														// װ�����õ���װ��ֵ
}


// WWDG�жϺ���
void WWDG_IRQHandler() {
	WWDG_SetCounter(CountValueMax);									// ��װ�أ���ֹϵͳ��λ
	WWDG_ClearFlag();																// ���WWDG��ǰ�жϱ�־
}
