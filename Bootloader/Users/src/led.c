/** 板载LED灯模块（验证通过） **/	
#include "led.h"


// LED小灯初始化（PB7）
void Led_Init() {
	
	GPIO_InitTypeDef GPIO_InitStructre;										// 定义一个GPIO结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	// 使能PC端口时钟
	
	GPIO_InitStructre.GPIO_Pin = GPIO_Pin_7;							// PB7口启用
	GPIO_InitStructre.GPIO_Mode = GPIO_Mode_Out_PP; 			// 推挽输出
	GPIO_InitStructre.GPIO_Speed = GPIO_Speed_50MHz; 			// IO口输出速度

	GPIO_Init(GPIOC, &GPIO_InitStructre); 								// 将前面设置的值应用到GPIOC上
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);										// 初始状态使PC7 IO口输出低电平
	
}


// 设置LED小灯状态
void Led_Set(int State) {
	
	if (State&1) {
		GPIO_SetBits(GPIOC, GPIO_Pin_7);		// 使PC7 IO口输出高电平
	} else {
		GPIO_ResetBits(GPIOC, GPIO_Pin_7);	// 使PC7 IO口输出低电平
	} 
}
