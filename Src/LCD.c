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
 * offset is how many pixels the text should be pushed to the left (to create a scrolling effect over multiple calls)
 */
void lcd_write_string(char s[], uint8_t slice, uint8_t line,uint8_t *LCDbuffer_p, uint8_t *remainBytes_p)
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
			else
			{
				//Saves the rest of the string that couldnt fit the lcd in remainBytes
				for(int k = i; k < strlen(s); k++)
				{
					for(int l = 0; l < 5;l++)
					{
						if(k == i)
						{
							*(remainBytes_p + l + line*128) = character_data[s[k]-0x20][l+j];
							if(l+j == 4){break;}
						}
						else
						{
							*(remainBytes_p + (k-1 - i)*5 + l + j - 1 + line*128) = character_data[s[k]-0x20][l]; //try -1 here
						}
					}
				}
				return;
			}

		}
	}
}

//right = 1 (or any other non zero) for right direction and right = 0 for left direction
void lcd_scrolling_text(uint8_t *LCDbuffer_p, uint8_t line, uint8_t *remainBytes_p, uint8_t right)
{
	/*
	Shifts LCDbuffer to the left or right by 1
	* New bytes shifted in from the right should be the remaining part of the string (if any).
	* If no left of remaining part use the parts of the string that were pushed out the left side.
	* If nothing has been pushed out yet print blank spaces.
	*/

	uint16_t lineOffset = line*128;

	if(right)
	{
		uint8_t lastIndex = 0;

		//Shifts the remainingByte array one to the right
		for(int i = 127; i > 0; i--)
		{
			*(remainBytes_p+lineOffset+i) = *(remainBytes_p+i-1+lineOffset);
		}

		//Saves the byte about to be pushed out:
		*(remainBytes_p+lineOffset) = *(LCDbuffer_p+lineOffset+127);

		//Shifts the buffer 1 to the right
		for(int i = 127; i > 0; i--)
		{
			*(LCDbuffer_p+i+lineOffset) = *(LCDbuffer_p+i+lineOffset-1);
		}

		for(int i = 0; i < 128; i++)
		{
			if(*(remainBytes_p+i+lineOffset) == 0xAA) //This is true at i = 3?!??
			{
				//Come back here
				lastIndex = i-1;
				break;
			}
		}

		//On a debug run lastIndex is 2 here ?!?!?

		//The last element shifted in is the first element in remainbytes (on that line)
		*(LCDbuffer_p+lineOffset) = *(remainBytes_p+lineOffset+lastIndex);
		*(remainBytes_p+lineOffset+lastIndex) = 0xAA;

	}
	else
	{
		//saves the byte ,in lcdbuffer that is about to be shifted out, in the first 'empty' (!= 0xAA) spot in remainbytes
		for(int i = 0; i < 128; i++)
		{
			if(*(remainBytes_p+i+lineOffset) == 0xAA)
			{
				*(remainBytes_p+i+lineOffset) = *(LCDbuffer_p+lineOffset);
				break;
			}
		}

		//shift everything except the last element one to the left
		for(int i = 0; i < 127; i++)
		{
			*(LCDbuffer_p+i+lineOffset) = *(LCDbuffer_p+i+lineOffset+1);
		}

		//The last element shifted in is the first element in remainbytes (on that line)
		*(LCDbuffer_p+127+lineOffset) = *(remainBytes_p+lineOffset);

		//Shifts everything on the specific line in remainbytes one to the left except the last where 0xAA (empty) is inserted
		for(int i = 0; i < 127; i++)
		{
			*(remainBytes_p+i+lineOffset) = *(remainBytes_p+i+lineOffset+1);
		}
		*(remainBytes_p+127+lineOffset) = 0xAA;
	}
}

void lcd_scroll_vertical(uint8_t slice1,uint8_t slice2,uint8_t *LCDbuffer_p, uint8_t *remainBytes_p, uint8_t up)
{
	/* METHOD:
	 * 1. For each byte in the LCDbuffer remember the bit that is about to be shifted out.
	 * 2. Then bitshift all bytes in the given direction.
	 * 3. Insert the saved bits in the correct positions.
	 * 4. Repeat step 1-3 for the 'remaining bytes buffer'.
	*/
}

/*
 * See lcd_sprites for the sprites that the type parameter pick between
 */
void lcd_draw_sprite(uint8_t * LCDbuffer,int16_t slice, int16_t line, uint8_t type)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 40; j++)
		{
			if(lcd_sprites[type][i][j] != 0x00 && i+line < 4 && slice+j < 128 && i+line >= 0 && slice+j >= 0)
			{
				*(LCDbuffer + slice + (line+i)*128 + j) |= lcd_sprites[type][i][j];
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

