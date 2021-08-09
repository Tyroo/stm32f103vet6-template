/* Flash����ģ�飨δ��֤�� */
/*************************************************************
*		BootLoader	*		Download	 *	 Programs   *		Standby		 *
**************************************************************/
#include "flash.h"

FLASH_CONFIG Flash_Configure;	// ����һ��Flash���ýṹ�����


// ��ʼ��Flashģ��
void Flash_Init() {
	Flash_Configure.START_ADDR = (u32)0x08000000;	// ����������ʼ��ַ
	Flash_Configure.END_ADDR = (u32)0x0807FFFF;		// �������������ַ
	Flash_Configure.PAGE_SIZE = (u16)2048;					// ��������ÿҳ��������2k��,��λ��bit��
}


// ��ָ����ַд������
void Flash_Write(u32 Addr, u16 *Data, u16 DataSize) {
	
  u16 ErasePageNum = DataSize / 1024;
	u16 ErasePageStart = ((Addr - Flash_Configure.START_ADDR) / Flash_Configure.PAGE_SIZE);
	
	ErasePageStart = ErasePageStart*2048 + Flash_Configure.START_ADDR;
	
	
	if (DataSize%1024) ErasePageNum += 1;
	
  // �����ַ�Ϸ���У��
  if (Addr<Flash_Configure.START_ADDR ||
		Addr - Flash_Configure.END_ADDR < (DataSize*2)) {
    return;
  }
  
  // ����FLASH
  FLASH_Unlock();
  
  // ��ҳ����
	Flash_Erase(ErasePageStart, ErasePageNum);

  // ��ÿ16λд��
  for(int Index=0;Index<DataSize;Index+=2) {
    FLASH_ProgramHalfWord((u32)(Addr + Index),  *(Data+Index));
  }
	
  // ����FLASH
  FLASH_Lock();
}


// ����һ��ҳ��������
void Flash_Erase(u32 StartPageAddr, u16 PageNum) {
	
	for(int Index=0;Index<PageNum;Index++) {
    FLASH_ErasePage((uint32_t)(StartPageAddr + Index*2048));
  }
}


// ��ȡָ����ַ������
vu16 Flash_Read(u32 Addr) {
	return *(vu16*)(Addr);
}
