/*
 * enemy.c
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#include "bulletManager.h"
#include "entityHandler.h"
#include "PuTTYSprites.h"
#include "vec.h"
#include "enemy.h"

void initEnemy(entity_t * entity, enemy_t * enemy, uint8_t type, uint8_t height)
{
	enemy->entity = entity;
	enemy->type = type;
	enemy->entity->height = height;
}

void enemyShoot(bulletManager_t *bulletManager,entityHandler_t *entHand,enemy_t * enemy)
{
	spawnBullet(bulletManager, entHand, getXint(&(enemy->entity->pos)), getYint(&(enemy->entity->pos)),0,1,0,1,enemy->entity->height);
}

