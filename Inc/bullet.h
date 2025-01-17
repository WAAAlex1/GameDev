#ifndef BULLET_H_
#define BULLET_H_

#include <stdint.h>
#include "entity.h"

typedef struct {
	entity_t *entity;
	uint8_t type;
	uint8_t friendly;
} bullet_t;

void initBullet(bullet_t *bullet, entity_t *entity, uint8_t type, uint8_t friendly);

#endif /* BULLET_H_ */
