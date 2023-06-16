/*
 * bulletManager.h
 *
 *  Created on: 16. jun. 2023
 *      Author: georg
 */

#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#include <stdint.h>

typedef struct{
	bullet_t bulletArray[64];
} bulletManager_t;

void spawnBullet(bulletManager_t *bulletManager, entityHandler_t *entHand,bullet_t *bullet, uint8_t x, uint8_t y, uint8_t bulletType, uint8_t height);

#endif /* BULLETMANAGER_H_ */
