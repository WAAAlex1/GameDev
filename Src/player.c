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
#include "player.h"

void initPlayer(entity_t *entity, player_t *player, uint8_t num){
	player->entity = entity;
	player->playerNum = num;
	player->gunSide = 1; //1 = LEFT | -1 = RIGHT
	player->powerUp = 0;

}

void changeGunside(player_t *player){
	if(player->gunSide == 1){
		player->gunSide = -1;
	} else {
		player->gunSide = 1;
	}
}

void getPowerUp(player_t *player, uint8_t num){
	if(num != 0){player->powerUp = num;}
}

void drawPlayer(player_t *player){
	if(player->gunSide == 1){
		ui_draw_sprite(0, 15, 0, getXint(&(player->entity->pos)), getYint(&(player->entity->pos)));
	} else {
		ui_draw_sprite(1, 15, 0, getXint(&(player->entity->pos)), getYint(&(player->entity->pos)));
	}
}


void clearPlayer(player_t *player){
	if(player->gunSide == 1){
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






