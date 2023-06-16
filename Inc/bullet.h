/*
 * bullet.h
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <stdint.h>

typedef struct {
	entity_t *entity;
	uint8_t type;
	uint8_t height;
} bullet_t;


#endif /* BULLET_H_ */
