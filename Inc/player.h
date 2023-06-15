/*
 * player.h
 *
 *  Created on: 14. jun. 2023
 *      Author: frede
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdint.h>
#include "vec.h"
#include "entity.h"

typedef struct {
	entity_t entity;
	uint8_t playerNum;
	int8_t gunSide;
	uint8_t powerUp;
} player_t;

void initPlayer(entity_t *entity, player_t *player, uint8_t num);
void changeGunside(player_t *player);
void getPowerUp(player_t *player, uint8_t num);
void drawPlayer(player_t *player);
void clearPlayer(player_t *player);

#endif /* PLAYER_H_ */
