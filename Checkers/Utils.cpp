#include <windows.h>
#include "Utils.h"
//#include "Checkers.cpp"

extern COORD BOARD_COORDS[5][5];
extern COORD coord;

/* Moves cursor to x, y position */
void gotoxy(int x,int y){
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

/* Moves cursor position to given row / collum of BOARD_ARRAY */
void gotoSquare(int x, int y){
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),BOARD_COORDS[x][y]);
}

/* Resizes console window */
void resizeWindow() {
	HANDLE hOut; //Windows output handle
	SMALL_RECT newScreenSize; //Rectangle containing the new dimensions
	SetConsoleTitle(TEXT( "Draughts - ALPHA" ));
	//Defining the dimensions of our window
	newScreenSize.Left = 0; //(Upper left)
	newScreenSize.Right = 79; //(Bottom right)
	newScreenSize.Top = 0;
	newScreenSize.Bottom = 38; //Height of window
	hOut = GetStdHandle(STD_OUTPUT_HANDLE); //Loading the handle
	SetConsoleWindowInfo(hOut, TRUE, &newScreenSize);
}

/* Changes console text colour */
void setColour(const int foreground, const int background) {
	int Colour = foreground + (background * 16);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, Colour);
	return;
}