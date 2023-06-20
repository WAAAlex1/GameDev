/*
 * enemy.h
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <stdint.h>
#include "bulletManager.h"
#include "vec.h"

typedef struct {
	entity_t *entity;
	uint8_t type;
} enemy_t;

void initEnemy(entity_t * entity, enemy_t * enemy, uint8_t type);
void enemyShoot(bulletManager_t *bulletManager, entityHandler_t *entHan, enemy_t * enemy);

#endif /* ENEMY_H_ */
