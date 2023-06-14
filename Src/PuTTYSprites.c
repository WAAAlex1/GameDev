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
 *  ALL SPRITES 5x5 - NOT USED INDICES FILLED WITH "?" (0x3F)
 *	ALL SPRITES SMALLER THAN 6x6 ARE LEFT-TOP-ALLIGNED
*/

const char spriteArray[8][4][5] = {

		// PLAYER WITH LEFT GUN (4x4)
		{{0x3F,0x2F,0xC1,0x5C,0x3F},
		{0xAE,0xB9,0xDB,0xBA,0x3F},
		{0x3F,0xBA,0xDB,0xBA,0x3F},
		{0x3F,0xBE,0x3F,0xBE,0x3F}},
		// PLAYER WITH RIGHT GUN (4x4)
		{{0x3F,0x2F,0xC1,0x5C,0x3F},
		{0x3F,0xBA,0xDB,0xCC,0xAF},
		{0x3F,0xBA,0xDB,0xBA,0x3F},
		{0x3F,0xBE,0x3F,0xBE,0x3F}},
		// Enemy spaceShip (4x4)
		{{0xCF,0x3F,0x3F,0xCF,0x3F},
		{0xC8,0xDB,0xDB,0xBC,0x3F},
		{0x3F,0x5C,0x2F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F}},
		// small Asteroid (1x1)
		{{0xDC,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F}},
		// medium Asteroid (2x2)
		{{0xDC,0xDC,0x3F,0x3F,0x3F},
		{0xDF,0xDF,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F}},
		// big Asteroid (4x3)
		{{0xDC,0xDC,0xDC,0xDC,0x3F},
		{0xDB,0xDB,0xDB,0xDB,0x3F},
		{0xDF,0xDF,0xDF,0xDF,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F}},
		// bullet
		{{0x6F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F}},
		// mega bullet
		{{0x5B,0xDB,0x5D,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F},
		{0x3F,0x3F,0x3F,0x3F,0x3F}},
};

///sadasd
void ui_draw_sprite(uint8_t index, uint8_t FGC, uint8_t BGC, uint8_t x, uint8_t y){
	gotoxy(x, y);

	for(uint8_t i = 0; i <= 3; i++){
		for(uint8_t j = 0; j <= 4; j++){
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
		moveCursorX(5,0);
	}
}
