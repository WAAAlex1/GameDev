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
#include "bulletManager.h"
#include "entityHandler.h"

typedef struct {
	entity_t * entity;
	uint8_t playerNum;
	int8_t gunSide;
	uint8_t powerUp;
	int8_t HP;
	uint8_t crosshairX;
	uint8_t crosshairY;
} player_t;

void initPlayer(entity_t *entity, player_t *player, uint8_t num);
void changeGunside(player_t *player);
void getPowerUp(player_t *player, uint8_t num);
void drawPlayer(player_t *player);
void clearPlayer(player_t *player);
void isAlive(player_t * player);
void damagePlayer(player_t *ptr, int8_t x);
void updatePlayerVel(player_t *player, char input);
void damagePlayer(player_t *ptr, int8_t x);
void playerShoot(player_t *ptr, bulletManager_t *bulletManager,entityHandler_t *entHan, uint8_t bulletType, uint8_t height);
void updateCrosshair(player_t *ptr,uint8_t joystickVal);
void usePowerUp(player_t * ptr, bulletManager_t * bulletManager,entityHandler_t * entHan);
void checkPlayerCollision(player_t * ptr, entityHandler_t * array);

#endif /* PLAYER_H_ */
