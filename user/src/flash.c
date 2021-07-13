/* Flash����ģ�飨δ��֤�� */
/*************************************************************
*		BootLoader	*		Download	 *	 Programs   *		Standby		 *
**************************************************************/
#include "flash.h"

FLASH_CONFIG Flash_Configure;	// ����һ��Flash���ýṹ�����

// ��ʼ��Flashģ��
void Flash_Init() {
	
	Flash_Configure.START_ADDR = 0x00008000;	// ����������ʼ��ַ
	Flash_Configure.END_ADDR = 0x0807FFFF;		// �������������ַ
	Flash_Configure.PAGE_SIZE = 2048;			// ��������ÿҳ������
}


// ��ָ����ַд������
void Flash_Write(u32 Addr, u16 *Data) {
	
  u16 DataSize = sizeof(Data);
  u16 ErasePageNum = (int)(DataSize / Flash_Configure.PAGE_SIZE + 0.5);
  u16 ErasePageStart = (DataSize - Flash_Configure.START_ADDR) / Flash_Configure.PAGE_SIZE;
  
  // �����ַ�Ϸ���У��
  if (Addr<Flash_Configure.START_ADDR ||
  Addr - Flash_Configure.END_ADDR < DataSize) {
    return;
  }
  
  // ����FLASH
  FLASH_Unlock();
  
  // ��ҳ����
	Flash_Erase(ErasePageStart, ErasePageNum);

  
  // ��ÿ16λд��
  for(int Index=0;Index<DataSize;Index+=2) {
    FLASH_ProgramHalfWord(Addr + Index,  Data[Index/2]);
  }
  
  // ����FLASH
  FLASH_Lock();
}


// ����һ��ҳ��������
void Flash_Erase(u32 StartPageAddr, u16 PageNum) {
	  for(int Index=0;Index<PageNum;Index++) {
    FLASH_ErasePage(StartPageAddr + Index * Flash_Configure.PAGE_SIZE);
  }
}


// ��ȡָ����ַ������
vu16 Flash_Read(u32 *Addr) {
	return *(vu16*)(Addr);
}
