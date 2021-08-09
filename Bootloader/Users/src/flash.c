/* Flash操作模块（未验证） */
/*************************************************************
*		BootLoader	*		Download	 *	 Programs   *		Standby		 *
**************************************************************/
#include "flash.h"

FLASH_CONFIG Flash_Configure;	// 定义一个Flash配置结构体变量


// 初始化Flash模块
void Flash_Init() {
	Flash_Configure.START_ADDR = (u32)0x08000000;	// 配置闪存起始地址
	Flash_Configure.END_ADDR = (u32)0x0807FFFF;		// 配置闪存结束地址
	Flash_Configure.PAGE_SIZE = (u16)2048;					// 配置闪存每页的容量（2k）,单位（bit）
}


// 向指定地址写入数据
void Flash_Write(u32 Addr, u16 *Data, u16 DataSize) {
	
  u16 ErasePageNum = DataSize / 1024;
	u16 ErasePageStart = ((Addr - Flash_Configure.START_ADDR) / Flash_Configure.PAGE_SIZE);
	
	ErasePageStart = ErasePageStart*2048 + Flash_Configure.START_ADDR;
	
	
	if (DataSize%1024) ErasePageNum += 1;
	
  // 输入地址合法性校验
  if (Addr<Flash_Configure.START_ADDR ||
		Addr - Flash_Configure.END_ADDR < (DataSize*2)) {
    return;
  }
  
  // 解锁FLASH
  FLASH_Unlock();
  
  // 按页擦除
	Flash_Erase(ErasePageStart, ErasePageNum);

  // 按每16位写入
  for(int Index=0;Index<DataSize;Index+=2) {
    FLASH_ProgramHalfWord((u32)(Addr + Index),  *(Data+Index));
  }
	
  // 加锁FLASH
  FLASH_Lock();
}


// 擦除一定页数的数据
void Flash_Erase(u32 StartPageAddr, u16 PageNum) {
	
	for(int Index=0;Index<PageNum;Index++) {
    FLASH_ErasePage((uint32_t)(StartPageAddr + Index*2048));
  }
}


// 读取指定地址的数据
vu16 Flash_Read(u32 Addr) {
	return *(vu16*)(Addr);
}
