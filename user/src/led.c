/** ����LED��ģ�飨��֤ͨ���� **/	
#include "led.h"


// LEDС�Ƴ�ʼ����PB7��
void Led_Init() {
	
	GPIO_InitTypeDef GPIO_InitStructre;										// ����һ��GPIO�ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	// ʹ��PC�˿�ʱ��
	
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_7;							// PB7������
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP; 			// �������
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz; 			// IO������ٶ�

	GPIO_Init(GPIOC, &GPIO_InitStructre); 								// ��ǰ�����õ�ֵӦ�õ�GPIOC��
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);										// ��ʼ״̬ʹPC7 IO������͵�ƽ
	
}


// ����LEDС��״̬
void Led_Set(int State) {
	
	if (State&1) {
		GPIO_SetBits(GPIOC, GPIO_Pin_7);		// ʹPC7 IO������ߵ�ƽ
	} else {
		GPIO_ResetBits(GPIOC, GPIO_Pin_7);	// ʹPC7 IO������͵�ƽ
	} 
}
