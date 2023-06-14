/*
 * player.c
 *
 *  Created on: 14. jun. 2023
 *      Author: frede
 */

#include "player.h"

void initPlayer(player_t *player, uint8_t num){
	player->playerNum = num;
	player->gunSide = 1; //1 = LEFT | -1 = RIGHT
	player->powerUp = 0;
	player->x = 40;
	player->y = 23;
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
		ui_draw_sprite(0, 15, 0, player->x, player->y);
	} else {
		ui_draw_sprite(1, 15, 0, player->x, player->y);
	}

}

void clearPlayer(player_t *player){

}

