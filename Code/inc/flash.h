#ifndef _FLASH_H_
#define _FLASH_H_

#include "stm32f1xx.h"

#define	FML_FLASH_PAGE			            0x08040000
#define	FML_FLASH_FLAG_ADRESS           0x08040000
#define	IN_FML_DATA_ADRESS              0x08040004
#define	OUT_FML_DATA_ADRESS             0x08040008
#define	DRAIN_FML_DATA_ADRESS           0x0804000C

#define	FML_FLASH_KEY 			            0x22061990

void FlashUnlock (void);
void FlashLock (void);
void FlashAllErase (void);
void FlashErase(uint32_t pageAddress);
uint32_t FlashReadData (uint32_t address);
void FlashWriteData(uint32_t address, uint32_t data);

#endif //_FLASH_H_
