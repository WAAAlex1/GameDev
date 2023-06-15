/*
 * memory.h
 *
 *  Created on: 9. jun. 2023
 *      Author: frede
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>

uint16_t readMemory(uint16_t offset);
void saveToMemory(uint16_t array[], uint8_t len);
void clearMemory();

#endif /* MEMORY_H_ */
