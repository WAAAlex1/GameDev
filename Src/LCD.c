/*
 * LCD.c
 *
 *  Created on: 7. jun. 2023
 *      Author: georg
 */
#include "stdio.h"
#include "string.h"
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "charset.h"
#include "stopwatch.h"
#include "lcdSprites.h"
#include "LCD.h"


void initLCD()
{
	lcd_init();
}
/*
 * X = slice is [0;127] and Y = Line is [0;3]
 */
void lcd_write_string(char s[], uint8_t slice, uint8_t line,uint8_t *LCDbuffer_p)
{
	//Draws the string at the start position (only the part that can fit the rest of the line)
	for(int i = 0; i < strlen(s); i++)
	{
		for(int j = 0; j < 5; j++)
		{
			if(slice+i*5+j <= 127)
			{
				*(LCDbuffer_p+slice+i*5+j+line*128) = character_data[s[i]-0x20][j];
			}
		}
	}
}

/*
 * See lcd_sprites for the sprites that the type parameter pick between
 */
void lcd_draw_sprite(uint8_t * LCDbuffer,int16_t slice, int16_t line, uint8_t type, uint8_t mirror)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		for(int16_t j = (mirror ? 39 : 0); (mirror ? j >= 0 : j < 40); j += (mirror ? -1 : 1))
		{
			if(lcd_sprites[type][i][j] != 0x00 && i+line < 4 && slice+(mirror ? 39-j : j) < 128 && i+line >= 0 && slice+(mirror ? 39-j : j) >= 0)
			{
				*(LCDbuffer + slice + (line+i)*128 + (mirror ? 39-j : j)) |= lcd_sprites[type][i][j];
			}
		}
	}
}

void lcd_draw_crosshair(uint8_t * LCDbuffer, uint8_t slice, uint8_t line)
{
	uint8_t sprite[8] = {0x3C, 0x5A, 0x99, 0xFF, 0xFF, 0x99, 0x5A, 0x3C};

	for(int i = 0; i < 8; i++)
	{
		if(slice + i < 128)
		{
			*(LCDbuffer + slice + line*128 + i) ^= sprite[i];
		}
	}

	//free sprite? or is it automatically freed?
}


void lcd_clear_all(uint8_t * LCDbuffer,uint8_t byte)
{
	memset(LCDbuffer,byte,512);
}

void lcd_game_over(uint8_t * LCDbuffer)
{
	lcd_clear_all(LCDbuffer,0x00);
	lcd_write_string("Game Over!",40,1,LCDbuffer);
	lcd_push_buffer(LCDbuffer);
}

