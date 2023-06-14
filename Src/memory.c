/*
 * memory.c
 *
 *  Created on: 9. jun. 2023
 *      Author: frede
 */

#include "memory.h"

//Example code to read high score
//printf("%s: %010lu\n", readHighscoreName(0), readHighscore(0));

uint16_t readMemory(uint16_t offset){
	//Typecast to uint16_t pointer and read the value at this location
	//Add 0x0800F800 to get to the correct memory page
	return *(uint16_t *)(0x0800F800 + offset * 2);
}

void saveToMemory(uint16_t array[], uint8_t len){
	//Return if you are attempting to save more data than we have space for
	if(len > 128){ return; }

	//Unlock memory
	FLASH_Unlock();
	FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR );

	//Erase page we want to write to
	FLASH_ErasePage(0x0800F800);

	//Write data to memory
	for(uint8_t i = 0; i < len; i++){
		FLASH_ProgramHalfWord(0x0800F800 + i*2, array[i]);
	}

	//Lock memory
	FLASH_Lock();
}

void clearMemory(){
	//Unlock memory
	FLASH_Unlock();
	FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR );

	//Erase page
	FLASH_ErasePage(0x0800F800);

	for(uint8_t i = 0; i < 20; i++){
		FLASH_ProgramHalfWord(0x0800F800 + i*2, 0);
	}

	//Lock memory
	FLASH_Lock();
}







