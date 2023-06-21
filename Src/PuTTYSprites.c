#include "ansi.h"
#include <stdint.h>
#include <stdio.h>
#include <PuTTYSprites.h>

/*  sprites:
 * 	spriteArray[0] = player (GUN LEFT)
 * 	spriteArray[1] = player (GUN RIGHT)
 *  spriteArray[2] = enemy spaceship
 *  spriteArray[3] = small asteroid
 *  spriteArray[4] = medium asteroid
 *  spriteArray[5] = big asteroid
 *  spriteArray[6] = bullet
 *	spriteArray[7] = mega Bullet
 *
*/

const char spriteArray[8][6][7] = {

		//0 PLAYER WITH LEFT GUN (4x4)
		{{0x3F,0x2F,0xC1,0x5C,0x3F,0x3F,0x3F},
		{0xAE,0xB9,0xDB,0xBA,0x3F,0x3F,0x3F},
		{0x3F,0xBA,0xDB,0xBA,0x3F,0x3F,0x3F},
		{0x3F,0xBE,0x3F,0xBE,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F}},
		//1 PLAYER WITH RIGHT GUN (4x4)
		{{0x3F,0x2F,0xC1,0x5C,0x3F,0x3F,0x3F},
		{0x3F,0xBA,0xDB,0xCC,0xAF,0x3F,0x3F},
		{0x3F,0xBA,0xDB,0xBA,0x3F,0x3F,0x3F},
		{0x3F,0xBE,0x3F,0xBE,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F}},
		//2 Enemy spaceShip (4x3)
		{{0xCF,0x3F,0x3F,0xCF,0x3F,0x3F,0x3F},
		{0xC8,0xDB,0xDB,0xBC,0x3F,0x3F,0x3F},
		{0x3F,0x5C,0x2F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F}},
		//3 small Asteroid (3x2)
		{{0xDC,0xDC,0xDC,0x3F,0x3F,0x3F,0x3F},
		{0xDF,0xDF,0xDF,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F}},
		//4 medium Asteroid (5x3)
		{{0xDC,0xDC,0xDC,0xDC,0xDC,0x3F,0x3F},
		{0xDB,0xDB,0xDB,0xDB,0xDB,0x3F,0x3F},
		{0xDF,0xDF,0xDF,0xDF,0xDF,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F}},
		//5 big Asteroid (7x4)
		{{0xDC,0xDC,0xDC,0xDC,0xDC,0xDC,0xDC},
		{0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB},
		{0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB},
		{0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F}},
		//6 bullet - 1x1
		{{0x6F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F}},
		//7 mega bullet - 3x1
		{{0x5B,0xDB,0x5D,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F}}
};


void ui_draw_sprite(uint8_t index, uint8_t FGC, uint8_t BGC, uint8_t x, uint8_t y){
	uint8_t i,j,subX,subY;

	switch(index){
	case(0):
		subX = 3;
		subY = 2;
		break;
	case(1):
		subX = 2;
		subY = 2;
		break;
	case(2):
		subX = 3;
		subY = 3;
		break;
	case(3):
		subX = 4;
		subY = 4;
		break;
	case(4):
		subX = 2;
		subY = 3;
		break;
	case(5):
		subX = 0;
		subY = 2;
		break;
	case(6):
		subX = 6;
		subY = 5;
		break;
	case(7):
		subX = 4;
		subY = 5;
	}

	gotoxy(x, y);

	for(i = 0; i <= 5-subY; i++){
		for(j = 0; j <= 6-subX; j++){
			color(FGC, BGC);
			if(spriteArray[index][i][j] == 0xBE){color(11,0);}
			if(spriteArray[index][i][j] == 0xCF){color(1,0);}
			if(x+j > 0 && x+j < 81 && y+i > 0 && y+i < 47){
				spriteArray[index][i][j] == 0x3F ? moveCursorX(1,1) : printf("%c", spriteArray[index][i][j]);
			} else {
				moveCursorX(1,1);
			}
		}
		moveCursorY(1,0);
		moveCursorX(7-subX,0);
	}
}

void ui_clear_sprite(uint8_t index, uint8_t FGC, uint8_t BGC, uint8_t x, uint8_t y){
	uint8_t i, j, subX, subY;
	switch(index){
		case(0):
			subX = 3;
			subY = 2;
			break;
		case(1):
			subX = 2;
			subY = 2;
			break;
		case(2):
			subX = 3;
			subY = 3;
			break;
		case(3):
			subX = 4;
			subY = 4;
			break;
		case(4):
			subX = 2;
			subY = 3;
			break;
		case(5):
			subX = 0;
			subY = 2;
			break;
		case(6):
			subX = 6;
			subY = 5;
			break;
		case(7):
			subX = 4;
			subY = 5;
		}

	gotoxy(x, y);
	color(FGC, BGC);

	for(i = 0; i <= 5-subY; i++){
		for(j = 0; j <= 6-subX; j++){
			if(x+j > 0 && x+j < 81 && y+i > 0 && y+i < 47){
				spriteArray[index][i][j] == 0x3F ? moveCursorX(1,1) : printf(" ");
			} else {
				moveCursorX(1,1);
			}
		}
		moveCursorY(1,0);
		moveCursorX(7-subX,0);
	}
}

int16_t offsetBulletCoordX(player_t *player)
{
	if(player->gunSide == 1){
		return getXint(&(player->entity->pos)) - 3;
	} else {
		return getXint(&(player->entity->pos)) + 7;
	}
}

int16_t offsetBulletCoordY(player_t *player)
{
	return getYint(&(player->entity->pos)) + 1;
}
