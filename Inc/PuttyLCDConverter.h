/*
 * PuttyLCDConverter.h
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */

#ifndef PUTTYLCDCONVERTER_H_
#define PUTTYLCDCONVERTER_H_

#include "stdint.h"
#include "stdio.h"
#include "stm32f30x_conf.h"
#include "30010_io.h"

int32_t con_getVecY(uint8_t slice);
int32_t con_getVecX(int8_t dir);
int8_t con_getDistanceX(uint8_t playerX, uint8_t entX);
uint8_t con_inCone(uint8_t playerX, uint8_t playerY, uint8_t entX, uint8_t entY);
int16_t con_posToSlice(uint8_t playerX, uint8_t playerY, uint8_t entX, uint8_t entY);


#endif /* PUTTYLCDCONVERTER_H_ */
