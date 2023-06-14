#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "sinLut.h"
#include "vec.h"
#include "ball.h"
#include "stopwatch.h"
#include "joystick.h"
#include "LCD.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "util.h"

void ballBouncing();
void initStopwatch();
void runStopwatch();
void initLCDMain();
void runLCDMain(char s[], uint8_t LCDbuffer[],uint16_t offset);

int main(void)
{
	// Setup communication with the PC
	uart_init(115200);


	srand(time(0));

	printf("%d", getRandomInterval(0,10));

	initLCDMain();

}

void initLCDMain()
{
	uint8_t LCDbuffer[512];
	uint8_t remainBytes[512];
	char s[] = "ABCDEFG";
	uint8_t tickCounter = 0;
	uint8_t xPos = 0;

	initTimerStuff(); //Comment to debug
	initLCD();

	lcd_clear_all(LCDbuffer,0x00);
	lcd_clear_all(remainBytes,0xAA);
	//lcd_write_string(s,10,1,LCDbuffer,remainBytes);


	lcd_draw_sprite(LCDbuffer,30,1,0);
	lcd_draw_sprite(LCDbuffer,70,0,1);
	lcd_draw_sprite(LCDbuffer,20,2,2);
	lcd_draw_sprite(LCDbuffer,0,0,3);
	lcd_draw_sprite(LCDbuffer,55,1,4);
	lcd_draw_sprite(LCDbuffer,-20,2,4);
	//lcd_draw_sprite(LCDbuffer,80,0,5);
	//lcd_draw_sprite(LCDbuffer,80,0,6);
	//lcd_push_buffer(LCDbuffer);
	//Spaceships:
	/*
	lcd_draw_sprite(LCDbuffer,0,3,7);
	lcd_draw_sprite(LCDbuffer,5,3,8);
	lcd_draw_sprite(LCDbuffer,16,3,9);
	lcd_draw_sprite(LCDbuffer,37,2,10);
	lcd_draw_sprite(LCDbuffer,81,0,11);

	lcd_draw_crosshair(LCDbuffer,80,2);
	*/

	lcd_push_buffer(LCDbuffer);

	while(1)
	{

		/*
		if(lcd_update())
		{
			tickCounter++;
		}

		if(tickCounter == 2)
		{
			lcd_clear_all(LCDbuffer,0x00);
			lcd_draw_sprite(LCDbuffer,xPos,0,11);
			xPos++;
			lcd_push_buffer(LCDbuffer);
			tickCounter = 0;
		}
		*/
	}
}

void runLCDMain(char s[], uint8_t LCDbuffer[], uint16_t offset)
{

}

void initStopwatch()
{
	initJoystick();

	resetStopwatch();

	clrscr();
	window(1,1,40,7,"Stopwatch",2);
	printTime(stopwatch.hours,stopwatch.minutes,stopwatch.seconds,stopwatch.hundredsthsOfSeconds,3,3,"Time since start");

	initTimerStuff();
}

void runStopwatch()
{
	uint8_t preJoystick = readJoystick();

	//printf("%d%d%d%d%d%d%d%d\n", (preJoystick & 64) >> 7, (preJoystick & 32) >> 6, (preJoystick & 32) >> 5, (preJoystick & 16) >> 4, (preJoystick & 8) >> 3, (preJoystick & 4) >> 2, (preJoystick & 2) >> 1, (preJoystick & 1) >> 0);
	window(1,1,40,7,"Stopwatch",2);
	printTime(stopwatch.hours,stopwatch.minutes,stopwatch.seconds,stopwatch.hundredsthsOfSeconds,3,3,"Time since start");


	if(readJoystick() != preJoystick)
	{
		preJoystick = readJoystick();
		switch(readJoystick())
		{
			case 2: //Down
				stopTimer();
				resetStopwatch();
				printTime(stopwatch.hours,stopwatch.minutes,stopwatch.seconds,stopwatch.hundredsthsOfSeconds,3,3,"Time since start");
				break;
			case 4://Left
				printTime(stopwatch.hours,stopwatch.minutes,stopwatch.seconds,stopwatch.hundredsthsOfSeconds,3,4,"Split time 1");
				break;
			case 8://Right
				printTime(stopwatch.hours,stopwatch.minutes,stopwatch.seconds,stopwatch.hundredsthsOfSeconds,3,5,"Split time 2");
				break;
			case 16: //Center
				toggleTimer();
				break;
			default:
				break;
		}
	}
}



void ballBouncing()
{
	//Init ball:
	ball_t ball;
	initBall(&ball);
	setPos(&ball,5,5);
	setVel(&ball,2,2);

	int32_t tickCounter = 0;
	int32_t collisionCounter = 0;

	while(1)
	{
		if(tickCounter == 1000000)//Based on a counter to slow it down after we rose the baud rate
		{
			clrscr();



			//Draw hits window:
			window(20,9,30,11,"",3);
			gotoxy(21,10);
			printf("Hits: %d", collisionCounter);

			//Ball
			updatePos(&ball,1);
			drawBall(&ball);


			//Draw window
			window(1,1,50,19,"",3);

			uint8_t normal = collision(&ball,1,1,50,19);

			switch(normal)
			{
				case 0: //Nothing hit
					break;
				case 1: //Side-wall hit
					ball.vel.x *= -1;
					collisionCounter++;
					break;
				case 2: //Top or bottom -wall hit
					ball.vel.y *= -1;
					collisionCounter++;
					break;
				case 3: //corner hit
					rotateVector(&(ball.vel), 256); //rotate by 180 degrees
					collisionCounter++;
					break;
				default:
					break;
			}

			tickCounter = 0;
		}
		tickCounter++;
	}
}
