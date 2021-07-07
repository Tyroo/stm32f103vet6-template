/** ��ʱ��ģ�� **/
#include "timer.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"

// ͨ�ö�ʱ��2�жϺ���
void Timer2_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* �������ýṹ�� */
	TIM_TimeBaseInitTypeDef TIM_InitStructre;							 // ����һ����ʱ���������ýṹ��
	
	/* ʹ��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 // ʹ�ܶ�ʱ��2ʱ��
	
	/* ���ö�ʱ��2 */
	TIM_InitStructre.TIM_ClockDivision =
		(uint16_t)(128 * (TimerClockDivision - 1));		 			 // ���ö�ʱ����ʱ�ӵķ�Ƶϵ��
	TIM_InitStructre.TIM_CounterMode = TIM_CounterMode_Up; // ���ö�ʱ������ģʽ�����ϼ�����
	TIM_InitStructre.TIM_Period = TimerCountValue; 				 // ���ü���������ֵ
	TIM_InitStructre.TIM_Prescaler = PrescalerValue;			 // ���ö�ʱ���ķ�Ƶ����
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStructre);						 // Ӧ��TIM2����
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);						 // ����TIM2��ʱ���жϸ���
		
	Nvic_Config(TIM2_IRQn, 0, 2, 1);											 // ����TIM2�ж����ȼ�
		
	TIM_Cmd(TIM2, ENABLE);																 // ʹ��TIM2��ʱ��
	
}
	

// ͨ�ö�ʱ��3��ʼ��������PWM���
void Timer3_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
	
	/* �������ýṹ�� */
	TIM_TimeBaseInitTypeDef TIM_InitStructre;							 // ����һ����ʱ���������ýṹ��
	TIM_OCInitTypeDef				TIM_OCInitStructre;						 // ����һ��ͨ�����ýṹ��
	GPIO_InitTypeDef				GPIO_InitStruetre;						 //	����һ��GPIO���ýṹ��
	
	/* ʹ��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 // ʹ��TIM3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 // GPIOCʱ��ʹ��
	
	/* GPIO���� */
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);			 // ��TIM3��ȫ��ӳ��
	GPIO_InitStruetre.GPIO_Mode = GPIO_Mode_AF_PP;				 // ����IO������Ϊ�����������
	GPIO_InitStruetre.GPIO_Pin = GPIO_Pin_7;							 // ����Ϊ��7��IO��
	GPIO_InitStruetre.GPIO_Speed = GPIO_Speed_50MHz;			 // ��������ٶ�Ϊ50MHz
	
	/* TIM3���� */
	TIM_InitStructre.TIM_Period = TimerCountValue;				 // ����TIM����װ��ֵ
	TIM_InitStructre.TIM_Prescaler = PrescalerValue;			 // ����TIM�ķ�Ƶ����
	TIM_InitStructre.TIM_ClockDivision = 
		(uint16_t)(128 * (TimerClockDivision - 1)); 				 // ���ö�ʱ����ʱ�ӵķ�Ƶϵ��
	TIM_InitStructre.TIM_CounterMode = TIM_CounterMode_Up; // ���ö�ʱ������ģʽ�����ϼ�����
		
	/* ��ʱ��ͨ������ */
	TIM_OCInitStructre.TIM_OCMode = TIM_OCMode_PWM1;			 // ����Ϊͨ�����ģʽΪPWM1ģʽ
	TIM_OCInitStructre.TIM_OutputState = TIM_OutputState_Enable; // ����Ƚ�ʹ��
	TIM_OCInitStructre.TIM_OCPolarity = TIM_OCPolarity_Low;	// �������Ϊ��
	
	/* ��ʼ�� */
	TIM_TimeBaseInit(TIM3, &TIM_InitStructre);						 // Ӧ��TIM3����
	GPIO_Init(GPIOA, &GPIO_InitStruetre);								   // Ӧ��GPIOC7����
	TIM_OC2Init(TIM3, &TIM_OCInitStructre);								 // Ӧ��ͨ������
	
	TIM_Cmd(TIM3, ENABLE);															   // ʹ��TIM3
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);						 // ����TIM3��ʱ���жϸ���
		
	Nvic_Config(TIM3_IRQn, 0, 2, 1);											 // ����TIM3�ж����ȼ�
	
}
	

// ͨ�ö�ʱ��5��ʼ�����������벶��
void Timer5_Init(uint16_t TimerCountValue, uint16_t PrescalerValue,
	int TimerClockDivision) {
		
		/* ʹ��ʱ�� */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		// ʹ��TIM5ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// ʹ��GPIOAʱ��
		
		/* �������ýṹ�� */
		TIM_TimeBaseInitTypeDef TIM_InitStructre;								// ���嶨ʱ�����ýṹ��
		TIM_ICInitTypeDef				TIM_ICInitStructre;							// ����TIM���벶�����ýṹ��
		
		/* ���ö�ʱ��5 */
		TIM_InitStructre.TIM_Period = TimerCountValue;					// ����TIM����װ��ֵ
		TIM_InitStructre.TIM_Prescaler = PrescalerValue;				// ����TIM�ķ�Ƶ����
		TIM_InitStructre.TIM_ClockDivision = 
			(uint16_t)(128 * (TimerClockDivision - 1)); 					// ���ö�ʱ����ʱ�ӵķ�Ƶϵ��
		TIM_InitStructre.TIM_CounterMode = TIM_CounterMode_Up;	// ���ö�ʱ������ģʽ�����ϼ�����
		
		/* ����TIM5���벶�� */
		TIM_ICInitStructre.TIM_Channel = TIM_Channel_1;				 					// ʹ��ͨ��1����Ϊ���벶��
		TIM_ICInitStructre.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 					// ���������Ƶ
		TIM_ICInitStructre.TIM_ICPolarity = TIM_ICPolarity_Rising;			// ���ò����������ź�
		TIM_ICInitStructre.TIM_ICSelection = TIM_ICSelection_DirectTI;	// ����IC1ֱ��ӳ����TI1��
		TIM_ICInitStructre.TIM_ICFilter = 0x00;													// ��ʹ�������˲�
		
		/* ��ʼ��TIM5 */
		TIM_TimeBaseInit(TIM5, &TIM_InitStructre);						 					// Ӧ��TIM5����
		TIM_ICInit(TIM5, &TIM_ICInitStructre);													// Ӧ��TIM5���벶������
		
		TIM_ITConfig(TIM5, TIM_IT_Update|TIM_IT_CC1, ENABLE);						// ʹ�ܸ��¡������ж�
		
		TIM_Cmd(TIM5, ENABLE);																					// ʹ��TIM5
}


// ��ʱ��2<�жϺ���>
void TIM2_IRQHandler() {
	
	ITStatus UpdateFlag = TIM_GetITStatus(TIM2, TIM_IT_Update);
	uint8_t  LedStatus = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7);
	
	if (UpdateFlag != RESET) {
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //���TIM2�����жϱ�־
		Led_Set(~LedStatus);
	
	}
}


// ��ʱ��3<�жϺ���>
void TIM3_IRQHandler() {
	
	static int PwmCount = 0;											// PWMռ�ձȼ�����
	static int PwmCountFlag = 0;									// PWMռ�ձȵ���/����־
	
	int PwmdutyChangePeriod = 200;								// PWMռ�ձȵ���/������
	
	ITStatus UpdateFlag = TIM_GetITStatus(TIM3, TIM_IT_Update);

	if (UpdateFlag != RESET) {
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //���TIM2�����жϱ�־
		
		if (PwmCount > PwmdutyChangePeriod - 1) 		// �������ﵽ��ֵ�����������ȴﵽ��ֵ������ʼ�ݼ�ʹ֮�䰵
			PwmCountFlag = 0;			
		
		if (PwmCount < 1) 	PwmCountFlag = 1;				// �������ﵽ��ֵ�����������ȴﵽ��ֵ������ʼ����ʹ֮����
		
		PwmCountFlag? PwmCount++ : PwmCount--;			// ���������PwmCountFlag������PwmCount
		
		TIM_SetCompare2(TIM3, PwmCount);						// ��ֵ���õ���Ӧ�Ĳ���ȽϼĴ�����
	}
}


// ��ʱ��5<�жϺ���>
void TIM5_IRQHandler() {
	
	static int CaptureValue = 0;	// TIM5����ĸߵ�ƽ����ֵ�����Զ���Ϊȫ�ֱ���
	static int CaptureStatus = 0;	// ����һ������״̬������0�����񵽵͵�ƽ��1�����񵽸ߵ�ƽ��2������ʱ
	
	ITStatus CaptureFlag = TIM_GetITStatus(TIM5, TIM_IT_CC1);	// �����־λ
	
	// ����1�������񵽵�ƽʱ���߲���ʱʱ����
	if (CaptureFlag != RESET || CaptureStatus == 2) {
		
		if (CaptureStatus > 0) {
			
			CaptureStatus = 0;
			CaptureValue = TIM_GetCapture1(TIM5);								// ��ȡ����ĸߵ�ƽ����ֵ
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);	// ����Ϊ�����ز���
			
		} else {
			
			CaptureStatus = 1;
			CaptureValue = 0;
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);	// ����Ϊ�½��ز���
			
		}
	// ����2����û�в��񵽵�ƽʱ����
	} else {	
		
		if (CaptureStatus == 1) CaptureValue++;	// ���֮ǰ�Ѿ������˸ߵ�ƽ����ʼ�ߵ�ƽ��������
		
		// ���ߵ�ƽ����������������ж�0x3f�λ�û�м�⵽�͵�ƽ�����ټ��͵�ƽ���ֶ���Ԥ�ߵ�ƽ����ֵ
		if (CaptureValue > 0x3f) {
			CaptureValue = 0;
			CaptureStatus = 2;		// ���״̬Ϊ����ʱ�����´ν����ж�ʱ��������1��ȡ�øߵ�ƽ����ֵ
		}
	}
	
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update|TIM_IT_CC1);	// ���TIM5���¡������жϱ�־λ
	
}
