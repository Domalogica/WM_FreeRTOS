#ifndef _FLASH_H_
#define _FLASH_H_

#include "stm32f1xx.h"

#define	IN_FML_DATA_ADRESS              0x08040000
#define	OUT_FML_DATA_ADRESS             0x08040004
#define	DRAIN_FML_DATA_ADRESS           0x08040008

void FlashUnlock (void);
void FlashLock (void);
void FlashAllErase (void);
void FlashErase(uint32_t pageAddress);
uint32_t FlashReadData (uint32_t address);
void FlashWriteData(uint32_t address, uint32_t data);

#endif //_FLASH_H_
