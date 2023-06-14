/*
 * PuttyLCDConverter.h
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */

#ifndef PUTTYLCDCONVERTER_H_
#define PUTTYLCDCONVERTER_H_

int32_t con_lcd_getVecY(uint8_t slice);
int32_t con_lcd_getVecX(int8_t dir);
uint8_t con_getDistanceX(uint8_t playerX, uint8_t entX);
int16_t con_posToSlice(uint8_t playerX, uint8_t playerY, uint8_t entX, uint8_t entY);


#endif /* PUTTYLCDCONVERTER_H_ */
