#include "stdio.h"
#include "string.h"
#include "ansi.h"
#define ESC 0x1B

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like	 that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr(){
	//Clear screen and home cursor. (Doesnt home for putty 0.7)
	printf("%c[2J",ESC);
}

void clreol(){
	printf("%c[2K",ESC);
}

void gotoxy(uint8_t x, uint8_t y){
	printf("%c[%d;%dH",ESC,y,x);
}

void underline(uint8_t on){
	if(on != 0){
		printf("%c[4m",ESC);
	}else{
		printf("%c[24m",ESC);
	}
}

void blink(uint8_t on){
	if(on != 0){
		printf("%c[5m",ESC);
	}else{
		printf("%c[25m",ESC);
	}
}

void inverse(uint8_t on){
	if(on != 0){
		printf("%c[7m",ESC);
	}else{
		printf("%c[27m",ESC);
	}
}

void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char title[], uint8_t style){
	if(style == 1)
	{
		//Top left corner
		gotoxy(x1,y1);
		printf("%c",201);
		//Top right corner
		gotoxy(x2,y1);
		printf("%c",187);
		//Bottom right corner
		gotoxy(x2,y2);
		printf("%c",188);
		//Bottom left corner
		gotoxy(x1,y2);
		printf("%c",200);

		// Borders for title:
		gotoxy(x1+1,y1);
		printf("%c",185);


		char windowTekst[] = " Window ";
		strcat(windowTekst, title);
		strcat(windowTekst, " ");

		inverse(1);
		for(int i = 0; i < x2-x1-2; i++)
		{
			gotoxy(x1+2+i,y1);
			if(i < strlen(windowTekst)){
				printf("%c",windowTekst[i]);
			}
			else if(i == strlen(windowTekst)){
				inverse(0);
				printf("%c",204);
			}
			else{
				printf("%c",205);
			}
		}
		inverse(0);
		for(int i = x1+1; i < x2; i++){
			gotoxy(i,y2);
			printf("%c",205);
		}
		for(int i = y1+1; i < y2; i++){
			gotoxy(x1,i);
			printf("%c",186);
			gotoxy(x2,i);
			printf("%c",186);
		}
	}
	else if(style == 2)
	{
		//Top left corner
		gotoxy(x1,y1);
		printf("%c",218);
		//Top right corner
		gotoxy(x2,y1);
		printf("%c",191);
		//Bottom right corner
		gotoxy(x2,y2);
		printf("%c",217);
		//Bottom left corner
		gotoxy(x1,y2);
		printf("%c",192);

		//Borders for title:
		gotoxy(x1+1,y1);
		printf("%c",180);
		gotoxy(x2-1,y1);
		printf("%c",195	);

		char windowTekst[] = " Window ";
		strcat(windowTekst, title);
		strcat(windowTekst, " ");

		inverse(1);
		for(int i = 0; i < x2-x1-3; i++)
		{
			gotoxy(x1+2+i,y1);
			if(i < strlen(windowTekst)){
				printf("%c",windowTekst[i]);
			}
			else{
				printf(" ");
			}
		}
		inverse(0);
		for(int i = x1+1; i < x2; i++){
			gotoxy(i,y2);
			printf("%c",196);
		}
		for(int i = y1+1; i < y2; i++){
			gotoxy(x1,i);
			printf("%c",179);
			gotoxy(x2,i);
			printf("%c",179);
		}
	}
	else if(style == 3)
	{
		//Top left corner
		gotoxy(x1,y1);
		printf("%c",201);
		//Top right corner
		gotoxy(x2,y1);
		printf("%c",187);
		//Bottom right corner
		gotoxy(x2,y2);
		printf("%c",188);
		//Bottom left corner
		gotoxy(x1,y2);
		printf("%c",200);

		for(int i = x1+1; i < x2; i++)
		{
			gotoxy(i,y2);
			printf("%c",205);
			gotoxy(i,y1);
			printf("%c",205);
		}

		for(int i = y1+1; i < y2; i++)
		{
			gotoxy(x1,i);
			printf("%c",186);
			gotoxy(x2,i);
			printf("%c",186);
		}
	}
}

void printTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t hundredsthsOfSeconds,uint8_t x, uint8_t y, char title[])
{
	gotoxy(x,y);
	printf("%s:",title);
	gotoxy(x+20,y);
	printf("%d:%02d:%02d:%02d",hours,minutes,seconds,hundredsthsOfSeconds);

}

void moveCursorX(uint8_t X, uint8_t UP){ //GOING RIGHT/LEFT
    printf("%c[%d%c", ESC, X,  UP ? 'C' : 'D');
}

void moveCursorY(uint8_t Y, uint8_t UP){ //GOING UP/DOWN
    printf("%c[%d%c", ESC, Y,  UP ? 'A' : 'B');
}



