#include "flash.h"

void FlashUnlock (void)
{
	FLASH->KEYR = FLASH_KEY1;
	FLASH->KEYR = FLASH_KEY2;
}

void FlashLock (void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}

void FlashAllErase (void)
{
	FLASH->CR |= FLASH_CR_MER;
	FLASH->CR |= FLASH_CR_STRT;
}

void FlashErase(uint32_t pageAddress) 
{
	while (FLASH->SR & FLASH_SR_BSY);
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = pageAddress;
	FLASH->CR |= FLASH_CR_STRT;
	while (!(FLASH->SR & FLASH_SR_EOP));
	FLASH->SR = FLASH_SR_EOP;
	FLASH->CR &= ~FLASH_CR_PER;
}

uint32_t FlashReadData (uint32_t address)
{
	return (*(__IO uint32_t*) address);
}

void FlashWriteData(uint32_t address, uint32_t data) 
{
	FLASH->CR |= FLASH_CR_PG;

	while((FLASH->SR & FLASH_SR_BSY)!=0);

	*(__IO uint16_t*)address = (uint16_t)data;

	while((FLASH->SR & FLASH_SR_BSY)!=0);

	address+=2;
	data>>=16;

	*(__IO uint16_t*)address = (uint16_t)data;

	while((FLASH->SR & FLASH_SR_BSY)!=0);

	FLASH->CR &= ~(FLASH_CR_PG);
}
