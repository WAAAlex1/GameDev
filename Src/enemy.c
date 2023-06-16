/*
 * enemy.c
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#include "PuTTYSprites.h"
#include "enemy.h"

void initEnemy(entity_t * entity, enemy_t * enemy, uint8_t type, uint8_t height)
{
	enemy->entity = entity;
	enemy->type = type;
	enemy->height = height;
}

void shoot(enemy_t * enemy) //needs spawn bullet function from bulletmanager
{

}

