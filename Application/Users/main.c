#include <stdio.h>
#include "stm32f10x.h"
#include "led.h"
#include "nvic.h"
#include "uart.h"
#include "exti.h"
#include "timer.h"
#include "delay.h"
#include "dma.h"
#include "adc.h"
#include "dac.h"




int main() {
	
	/* 变量定义 */
	uint8_t ADC1ChanneArray[1] = { 0x01 };
	
	/* 初始化模块配置 */
	Nvic_Init(2);									// 初始化NVIC模块，中断分组2
	Led_Init();										// 初始化LED模块
	Uart1_Init(115200);						// 初始化UART1模块
	Exti_Init();									// 初始化外部中断
	Delay_Init();									// 初始化延时模块
	Timer2_Init(9999, 7199, 1);		// 初始化TIM2模块
	
	// 初始化ADC1通道16
	Adc1_Init(ENABLE, DISABLE, ADC1ChanneArray, 1);
	// 开启ADC1的通道16的转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);							
	Dac_Init();										// 初始化DAC模块
	

//	float ChipTemperate = 0;
//	char ChipTemperateStr[] = "";
	
	int* Dac_CntArray = Dac_GenerCntArr_Sin();	// 生成DAC计数值数组
	
	while(1) {
		
//		if (Timer2_Flag&1) {
//			Timer2_Flag = 0;
//			ChipTemperate = Get_ChipTemperate(10);
//			sprintf(ChipTemperateStr, "Chip Temperate：%.2f℃.\n", ChipTemperate);
//			Uart1_Send(ChipTemperateStr);
//		}
		
		for(u8 Index=0;Index<DAC_CNT_RESOLUTION;Index++) {
			Delay_Ms(10);
			DAC_SetChannel1Data(DAC_Channel_1, *(Dac_CntArray + Index));	// 设置DAC计数值
		}
		
	}
}

