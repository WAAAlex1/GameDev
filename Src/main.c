#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "realLut.h"
#include "vectored.h"
#include "joystick.h"
#include "serialRead.h"
#include "stopwatch.h"
#include "sprites.h"

void sineTest();
void rotateTest();
void rgbJoystickTest();
void initStopwatch();
void runStopwatch();

int main(void)
{
	//initLED();
	//initJoystick();
	uart_init(115200);
	clrscrn();
	char temp;

	/*
	gotoxy(0,0);
	drawSprite(0, 15, 0);
	gotoxy(5,0);
	drawSprite(1, 15, 0);
	gotoxy(10,0);
	drawSprite(2, 15, 0);
	gotoxy(15,0);
	drawSprite(3, 15, 0);
	gotoxy(0,10);
	drawSprite(4, 15, 0);
	gotoxy(5,10);
	drawSprite(5, 15, 0);
	gotoxy(10,10);
	drawSprite(6, 15, 0);
	gotoxy(15,10);
	drawSprite(7, 15, 0);
	*/


	gotoxy(1, 1);
	uart_clear();



	while (1) {

	}
}

void initStopwatch()
{
    initJoystick();

    resetStopwatch();

    clrscrn();
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


void rgbJoystickTest(){
	uint8_t jsValold;
	uint8_t jsValnew;

	uart_init(9600);
	clrscrn();

	jsValold = readJoystick();

	while(1){
		jsValnew = readJoystick();
		if(jsValold != jsValnew){
			printf("%d%d%d%d%d%d%d%d\n", (jsValnew & 64) >> 7, (jsValnew & 32) >> 6, (jsValnew & 32) >> 5, (jsValnew & 16) >> 4, (jsValnew & 8) >> 3, (jsValnew & 4) >> 2, (jsValnew & 2) >> 1, (jsValnew & 1) >> 0);
			RGBJoystick(jsValnew);
			jsValold = jsValnew;
		}
	}
}

void rotateTest(){
	uart_init(9600);
	clrscrn();
	vector_t vec;
	initVector(&vec,1,2);
	rotateVectorByReference(&vec,256);
	printFix(expand(vec.x));
	printf("\t");
	printFix(expand(vec.y));
	printf("\n");
	initVector(&vec,6,4);
	rotateVectorByReference(&vec,-14);
	printFix(expand(vec.x));
	printf("\t");
	printFix(expand(vec.y));
	printf("\n");
	initVector(&vec,-4,-4);
	rotateVectorByReference(&vec,1280);
	printFix(expand(vec.x));
	printf("\t");
	printFix(expand(vec.y));
	printf("\n");
	initVector(&vec,-4,2);
	rotateVectorByReference(&vec,-50);
	printFix(expand(vec.x));
	printf("\t");
	printFix(expand(vec.y));
	printf("\n");

	while(1){}
}


void sineTest(){
	uart_init(9600);
	clrscrn();
	printf("Sinus:\n");
	printFix(expand(Sinosoid(0)));
	printf("\n");
	printFix(expand(Sinosoid(64)));
	printf("\n");
	printFix(expand(Sinosoid(-111)));
	printf("\n");
	printFix(expand(Sinosoid(923)));
	printf("\n");
	printf("Cosinus:\n");
	printFix(expand(Cosinoid(0)));
	printf("\n");
	printFix(expand(Cosinoid(64)));
	printf("\n");
	printFix(expand(Cosinoid(-111)));
	printf("\n");
	printFix(expand(Cosinoid(923)));
	printf("\n");

	while(1){}
}



