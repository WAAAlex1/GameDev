/*
 * player.h
 *
 *  Created on: 14. jun. 2023
 *      Author: frede
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdint.h>
#include "ansi.h"
#include "PuTTYSprites.h"

typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t playerNum;
	uint8_t gunSide;
	uint8_t powerUp;
} player_t;

void initPlayer(player_t *player, uint8_t num);
void changeGunside(player_t *player);
void getPowerUp(player_t *player, uint8_t num);
void drawPlayer(player_t *player);
void clearPlayer(player_t *player);

#endif /* PLAYER_H_ */
