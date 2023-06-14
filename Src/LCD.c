/*
 * LCD.c
 *
 *  Created on: 7. jun. 2023
 *      Author: georg
 */
#include "LCD.h"

//for lcd_getVecX
#define CONE_VIEW_WIDTH 32
#define CONE_VIEW_LENGTH 40
#define CONE_VIEW_ANGLE 44

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

uint8_t lcd_update()
{
	if(LCD_Flag == 1)
	{
		LCD_Flag = 0;
		return 1;
	}

	return 0;
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
 * type = 0 for 2x2 asteroid
 * type = 1 for 3x3 asteroid
 * type = 2 for enemy spaceship
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
	*(LCDbuffer + slice + line*128) ^= 0x3C;
	*(LCDbuffer + slice + line*128+1) ^= 0x5A;
	*(LCDbuffer + slice + line*128+2) ^= 0x99;
	*(LCDbuffer + slice + line*128+3) ^= 0xFF;
	*(LCDbuffer + slice + line*128+4) ^= 0xFF;
	*(LCDbuffer + slice + line*128+5) ^= 0x99;
	*(LCDbuffer + slice + line*128+6) ^= 0x5A;
	*(LCDbuffer + slice + line*128+7) ^= 0x3C;
}


void lcd_clear_all(uint8_t * LCDbuffer,uint8_t byte)
{
	memset(LCDbuffer,byte,512);
}

/*
 * Returns the fixed point 18.14 y coordinate for the unitvector in the direction given by the LCD slice
 *
 * to be moved to its own lcd to putty manager api file?
 *
 * Remember to also move the defined constants if the function is moved
 */
int32_t lcd_getVecY(uint8_t slice)
{
	//a bug might occur here if the (slice/4 - 16) is seen as 1 byte long instead of 4 bytes long.
	return (((slice / 4) - 16) << 14) / CONE_VIEW_LENGTH;
}

/*
 * Returns the fixed point 18.14 x coordinate for the unitvector in the given gunner direction
 *
 * for left gunner direction set dir = -1;
 * for right gunnner direction set dir = 1;
 */
int32_t lcd_getVecX(int8_t dir)
{
	return ((CONE_VIEW_LENGTH * dir) << 14) / CONE_VIEW_LENGTH;
}

/*
 * returns the slice for the entity to be drawn on
 */
int16_t puttyPosToLCD(uint8_t playerX, uint8_t playerY, uint8_t entX, uint8_t entY)
{


}

