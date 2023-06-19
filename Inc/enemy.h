/*
 * enemy.h
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <stdint.h>
#include "vec.h"
#include "entity.h"
#include "bulletManager.h"
#include "entityHandler.h"

typedef struct {
	entity_t *entity;
	uint8_t type;
	uint8_t height;
} enemy_t;


void initEnemy(entity_t * entity, enemy_t * enemy, uint8_t type, uint8_t height);
void enemyShoot(bulletManager_t *bulletManager,entityHandler_t *entHand,enemy_t * enemy);
#endif /* ENEMY_H_ */
