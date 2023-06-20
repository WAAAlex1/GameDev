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
#include "entityHandler.h"
#include "bulletManager.h"

typedef struct {
	entity_t *entity;
	uint8_t type;
} enemy_t;

void initEnemy(entity_t * entity, enemy_t * enemy, uint8_t type);
void enemyShoot(bulletManager_t *bulletManager,entity_t *entArr,enemy_t * enemy);

#endif /* ENEMY_H_ */
