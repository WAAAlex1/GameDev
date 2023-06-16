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

void initPlayer(entity_t *entity, player_t *player, uint8_t num){ //---------HER ER FUCKED---------
	player->entity = entity;
	player->playerNum = num;
	player->gunSide = 1; //1 = LEFT | -1 = RIGHT
	player->powerUp = 0;

}

void changeGunside(player_t *player){
	if(player->gunSide){
		player->gunSide = 0;
	} else {
		player->gunSide = 1;
	}
}

void getPowerUp(player_t *player, uint8_t num){
	player->powerUp = num;
}

void drawPlayer(player_t *player){
	if(player->gunSide == 1){
		ui_draw_sprite(0, 15, 0, player->entity->pos.x, player->entity->pos.y);
	} else {
		ui_draw_sprite(1, 15, 0, player->entity->pos.x, player->entity->pos.y);
	}
}

void clearPlayer(player_t *player){
	if(player->gunSide == 1){
		ui_clear_sprite(0, 15, 0, player->entity->pos.x, player->entity->pos.y);
	} else {
		ui_clear_sprite(1, 15, 0, player->entity->pos.x, player->entity->pos.y);
	}
}






