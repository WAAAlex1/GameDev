/*
 * LCD.h
 *
 *  Created on: 7. jun. 2023
 *      Author: georg
 */

#ifndef LCD_H_
#define LCD_H_



//lcd_reset() will reboot and reconfigure the LCD
//lcd_transmit_bye() is used to send data and commands to the display, but shouldn't be used unless I understand it
//lcd_push_buffer() transmits a byte array of size 512 to the LCD and shows the data. This is what I will use to update the display

void initLCD();
void lcd_write_string(char s[], uint8_t slice, uint8_t line,uint8_t *LCDbuffer_p, uint8_t *remainBytes_p);
uint8_t lcd_update();
void lcd_scrolling_text(uint8_t *LCDbuffer_p, uint8_t line, uint8_t *remainBytes_p,uint8_t right);
void lcd_scroll_vertical(uint8_t slice1,uint8_t slice2,uint8_t *LCDbuffer_p, uint8_t *remainBytes_p, uint8_t up);
void lcd_draw_sprite(uint8_t * LCDbuffer,int16_t slice, int16_t line, uint8_t type);
void lcd_draw_crosshair(uint8_t * LCDbuffer, uint8_t slice, uint8_t line);
void lcd_clear_all(uint8_t * LCDbuffer,uint8_t byte);


#endif /* LCD_H_ */
