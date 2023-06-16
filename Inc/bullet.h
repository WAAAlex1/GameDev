/*
 * bullet.h
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <stdint.h>
#include "entity.h"

typedef struct {
	entity_t *entity;
	uint8_t type;
	uint8_t height;
} bullet_t;

void initBullet(bullet_t *bullet, entity_t *entity, uint8_t type, uint8_t height);

#endif /* BULLET_H_ */
