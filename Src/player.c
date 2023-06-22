/*
 * player.c
 *
 *  Created on: 14. jun. 2023
 *      Author: frede
 */

#include <stdint.h>
#include "ansi.h"
#include "PuTTYSprites.h"
#include "vec.h"
#include "entity.h"
#include "PuttyLCDConverter.h"
#include "util.h"
#include "player.h"

void initPlayer(entity_t *entity, player_t *player, uint8_t num){
	player->entity = entity;
	player->playerNum = num;
	player->gunSide = 1; //1 = LEFT | -1 = RIGHT
	player->powerUp = 0;
	player->crosshairX = 63; //middle of LCD
	player->crosshairY = 1;
	player->entity->isActive = 1;
	player->HP = 3;
}

void updateCrosshair(player_t *ptr,uint8_t joystickVal)
{
	switch(joystickVal)
	{
		case 0x01:
			ptr->crosshairY = capInterval(ptr->crosshairY-1,0,3);
			break;
		case 0x02:
			ptr->crosshairY = capInterval(ptr->crosshairY-1,0,3);
			ptr->crosshairX = capInterval(ptr->crosshairX+8,0,127);
			break;
		case 0x04:
			ptr->crosshairX = capInterval(ptr->crosshairX+8,0,127);
			break;
		case 0x08:
			ptr->crosshairY = capInterval(ptr->crosshairY+1,0,3);
			ptr->crosshairX = capInterval(ptr->crosshairX+8,0,127);
			break;
		case 0x10:
			ptr->crosshairY = capInterval(ptr->crosshairY+1,0,3);
			break;
		case 0x20:
			ptr->crosshairY = capInterval(ptr->crosshairY+1,0,3);
			ptr->crosshairX = capInterval(ptr->crosshairX-8,0,127);
			break;
		case 0x40:
			ptr->crosshairX = capInterval(ptr->crosshairX-8,0,127);
			break;
		case 0x80:
			ptr->crosshairY = capInterval(ptr->crosshairY-1,0,3);
			ptr->crosshairX = capInterval(ptr->crosshairX-8,0,127);
			break;
		default:
			break;
	}
}

void changeGunside(player_t *player){
	if(player->gunSide == 1){
		player->gunSide = -1;
	} else {
		player->gunSide = 1;
	}
}

void drawPlayer(player_t *player)
{
	if(player->gunSide == 1)
	{
		ui_draw_sprite(0, 15, 0, getXint(&(player->entity->pos)), getYint(&(player->entity->pos)));
	} else {
		ui_draw_sprite(1, 15, 0, getXint(&(player->entity->pos)), getYint(&(player->entity->pos)));
	}
}


void clearPlayer(player_t *player)
{
	if(player->gunSide == 1)
	{
		ui_clear_sprite(0, 15, 0, getXint(&(player->entity->pos)), getYint(&(player->entity->pos)));
	} else {
		ui_clear_sprite(1, 15, 0, getXint(&(player->entity->pos)), getYint(&(player->entity->pos)));
	}
}

void isAlive(player_t * player){
	if(player->HP < 1) player->entity->isActive = 0;
}

//function to deal damage to an entity
//can also be used to "heal" an entity
void damagePlayer(player_t *ptr, int8_t x){
	ptr->HP -= x;
	ptr->HP = ptr->HP > 0 ? ptr->HP : 0;
	ptr->HP = ptr->HP > 3 ? 3 : ptr->HP;
}

void updatePlayerVel(player_t *player, char input){
	switch(input){
		case('w'):
			if(player->entity->vel.y > -1){
				updateVel(player->entity, 0, -1);
			}
			break;
		case('a'):
			if(player->entity->vel.x > -1){
				updateVel(player->entity, -1, 0);
			}
			break;
		case('s'):
			if(player->entity->vel.y < 1){
				updateVel(player->entity, 0, 1);
			}
			break;
		case('d'):
			if(player->entity->vel.x < 1){
				updateVel(player->entity, 1, 0);
			}
			break;
	}
}

void playerShoot(player_t *ptr, bulletManager_t *bulletManager,entityHandler_t *entHan, uint8_t bulletType, uint8_t height)
{
	spawnBullet(bulletManager,entHan,offsetBulletCoordX(ptr),offsetBulletCoordY(ptr),con_getVecX(ptr->gunSide),con_getVecY(ptr->crosshairX,ptr->gunSide),1,0,ptr->crosshairY, 1);
}

//check if player collides with an asteroid, enemy ship or bullet.
//damage player and set the other entity inactive if collision.
void checkPlayerCollision(player_t * ptr, entityHandler_t * array)
{
	uint8_t v;
	for(v = 1; v < ENTITY_ARR_LEN; v++) //avoids checking player itself
	{
		if(array->entityArray[v]->isActive && array->entityArray[v]->spriteIndex != 7) //cant collide with megabullet
		{
			if(detectEntityCollision(ptr->entity, array->entityArray[v]))
			{
				damagePlayer(ptr,1);
				destroyEntity(array->entityArray[v]);
			}
		}
	}
}

void usePowerUp(player_t * ptr, bulletManager_t * bulletManager,entityHandler_t * entHan){
	switch(ptr->powerUp){
		case(1): //restock HP
			ptr->HP = ptr->HP < 3 ? 3 : ptr->HP;
			ptr->powerUp = 0;
			break;
		case(2): //add shield
			ptr->HP += (ptr->HP < 4 ? 1 : 0);
			ptr->powerUp = 0;
			break;
		case(3): //spawn megabullet in front of player with velocity -2.
			spawnBullet(bulletManager,entHan,getXint(&(ptr->entity->pos))+1,getYint(&(ptr->entity->pos))-1, 0, -2, 0, 1, 0, 1);
			ptr->powerUp = 0;
			break;
		default:
			return;
	}
}
