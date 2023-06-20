/*
 * enemy.c
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#include "bullet.h"
#include "entity.h"
#include "bulletManager.h"
#include "entityHandler.h"
#include "PuTTYSprites.h"
#include "vec.h"
#include "enemy.h"

void initEnemy(entity_t * entity, enemy_t * enemy, uint8_t type)
{
	enemy->entity = entity;
	enemy->type = type; // = 0 for spaceship, = 1 for 1x1 asteroid, = 2 for 2x2 asteroid and = 3 for 3x3 asteroid
}

void enemyShoot(bulletManager_t *bulletManager,entity_t *entArr,enemy_t * enemy)
{
	spawnBullet(bulletManager, entArr, getXint(&(enemy->entity->pos)), getYint(&(enemy->entity->pos)),0,1,0,1,enemy->entity->height);
}

