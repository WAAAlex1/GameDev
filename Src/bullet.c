/*
 * bullet.c
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#include "entity.h"
#include "bullet.h"

void initBullet(bullet_t *bullet, entity_t *entity, uint8_t type)
{
	bullet->entity = entity;
	bullet->type = type;
}
