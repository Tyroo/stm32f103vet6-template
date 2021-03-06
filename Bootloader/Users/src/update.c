#include "update.h"


// 检测并处理更新，实现在线升级
void Update_Process() {

	// 判断Flash中的更新参数是否被置1
	volatile u16 UpdateFlag = Flash_Read(UPDATE_FLAG_ADDR);
	
	// 当UpdateFlag被置0时，表示需要更新，为全F或者1时不需要更新
	if (UpdateFlag == 0) {
		
		// 倒计时等待更新的到来
		Update_CountDown();
		
		// 上面的循环结束后，若检测到开始下载更新数据
		if (IsDownload == 1) {
			
			while(!IsDownload);	// 等待更新程序下载完成
			
			// 下载完成后，将UpdateFlag置1
			Flash_Write(UPDATE_FLAG_ADDR, (u16 *)1, 1);
		}
	} 
}


// 倒计时UPDATE_TIMEOUT秒等待开始更新
static void Update_CountDown() {
	
	u8 UpdateTimeout = UPDATE_TIMEOUT;
	
	// 当倒计时未结束且下载未开始时进入，IsDownload为uart模块的是否接收到数据标志
	while(UpdateTimeout>0 && IsDownload == 0) {
		
		if (Timer2_Flag == 1) {
			Timer2_Flag = 0;
			Uart1_Send("Please download update pack!");
			UpdateTimeout --;
		}
	}
}
