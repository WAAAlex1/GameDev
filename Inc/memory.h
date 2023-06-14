/*
 * memory.h
 *
 *  Created on: 9. jun. 2023
 *      Author: frede
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

uint16_t readMemory(uint16_t offset);
void saveToMemory(uint16_t array[], uint8_t len);
void clearMemory();

#endif /* MEMORY_H_ */
