#include "update.h"


void Update_Process() {

	// �ж�Flash�еĸ��²����Ƿ���1
	volatile u16 UpdateFlag = Flash_Read(UPDATE_FLAG_ADDR);
	
	// ��UpdateFlag����1ʱ����ʾ��Ҫ����
	if (UpdateFlag&1) {
		
		// ����ʱ�ȴ����µĵ���
		Update_CountDown();
		
		// �����ѭ������������⵽��ʼ���ظ�������
		if (IsDownload == 1) {
			
			while(!IsDownload);	// �ȴ����³����������
			
			// ������ɺ����Flash�е�UpdateFlag
			Flash_Write(UPDATE_FLAG_ADDR, 0, 1);
		}
	} 
}


// ����ʱUPDATE_TIMEOUT��ȴ���ʼ����
void Update_CountDown() {
	
	u8 UpdateTimeout = UPDATE_TIMEOUT;
	
	// ������ʱδ����������δ��ʼʱ���룬IsDownloadΪuartģ����Ƿ���յ����ݱ�־
	while(UpdateTimeout>0 && IsDownload == 0) {
		
		if (Timer2_Flag == 1) {
			Timer2_Flag = 0;
			Uart1_Send("Plase download update pack...");
			UpdateTimeout --;
		}
	}
}
