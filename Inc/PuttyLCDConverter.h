/*
 * PuttyLCDConverter.h
 *
 *  Created on: 14. jun. 2023
 *      Author: georg
 */

#ifndef PUTTYLCDCONVERTER_H_
#define PUTTYLCDCONVERTER_H_

#include "enemyManager.h"
#include "player.h"
#include "stdint.h"

int32_t con_getVecY(uint8_t slice, int8_t gunside);
int32_t con_getVecX(int8_t gunside);
int8_t con_getDistanceX(uint8_t playerX, uint8_t entX);
uint8_t con_inCone(uint8_t playerX, uint8_t playerY, uint8_t entX, uint8_t entY, int8_t gunside);
int16_t con_posToSlice(uint8_t playerX, uint8_t playerY, uint8_t entX, uint8_t entY, int8_t gunside);
void con_draw_putty_to_lcd(enemyManager_t *enemMan, player_t *player,uint8_t * LCDbuffer);

#endif /* PUTTYLCDCONVERTER_H_ */
