#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include "Utils.h"

/* Function prototypes */
// Gameplay
void drawBoard();
void fillBoard();
void runGame();
void playerTurn();
<<<<<<< HEAD
int compTurn();
=======
void compTurn();

>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
void highlightPiece(int, int, char);
void selectPiece();
int checkPiece(int, int, char);
int checkMove(int, int);
void movePiece(int, int, int, int, int);
<<<<<<< HEAD
void arduinoMovePiece(int, int, int, int);
// Serial
int serialSend();
int openSerial();
int closeSerial();
=======
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce

/* Global variable initialisation */
COORD coord={0,0};

/* Serial Coms variable intitialisation */
HANDLE hSerial;
DCB dcbSerialParams = {0};
COMMTIMEOUTS timeouts = {0};
DWORD dwBytesWritten = 0;
DWORD dwBytesRead = 0;
 
char dev_name[MAX_PATH];
char text_to_send[MAX_PATH];

// Top left corner of board
int cornerX = 20;	// Horizontal
int cornerY = 5;	// Vertical
// Top left X and Y
int tlX = cornerX + 3;
int tlY = cornerY + 2;

struct move 
{
	int origin[2];
	int moveTo[2];
	int jumpSize;
};

// Current BOARD_ARRAY value of current piece selected by user
int realPiece[2] = {0,0};
int realMove[2] = {0,0};

/* Text colors defined for SetColor() */
enum {
	BLACK = 0,
	DARK_BLUE = 1,
	DARK_GREEN = 2,
	TEAL = 3,
	DARK_RED = 4,
	DARK_PURPLE = 5,
	GOLD = 6,
	GREY = 7,
	DARK_WHITE = 8,
	BLUE = 9,
	GREEN = 10,
	CYAN = 11,
	RED = 12,
	PURPLE = 13,
	YELLOW = 14,
	WHITE = 15
};

/* Global game board array | 0 - Empty  | 1 - White | 2 - Black | 3 - white king | 4 - black king [ROW][COLUMN] */
int BOARD_ARRAY[5][5] = 
{
<<<<<<< HEAD
{0, 2, 0, 2, 0},
{2, 0, 2, 0, 2},
{0, 0, 0, 0, 0},
{1, 0, 1, 0, 1},
{0, 1, 0, 1, 0},
=======
{0, 2, 0, 2, 0, 2},
{2, 0, 2, 0, 2, 0},
{0, 0, 0, 0, 0, 0},
{0, 0, 4, 0, 0, 0},
{0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 0},
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
};

/* Global square colours | 1 - white | 2 - black [ROW][COLUMN] */
const int BOARD_COLOURS[5][5] = 
{
{2, 1, 2, 1, 2},
{1, 2, 1, 2, 1},
{2, 1, 2, 1, 2},
{1, 2, 1, 2, 1},
{2, 1, 2, 1, 2},
};

/* Screen coordinates of every board square [ROW][COLUMN]*/
COORD BOARD_COORDS[5][5] = 
{
{{tlX,tlY},    {tlX+6,tlY},    {tlX+12,tlY},    {tlX+18,tlY},    {tlX+24,tlY}},
{{tlX,tlY+4},  {tlX+6,tlY+4},  {tlX+12,tlY+4},  {tlX+18,tlY+4},  {tlX+24,tlY+4}},
{{tlX,tlY+8},  {tlX+6,tlY+8},  {tlX+12,tlY+8},  {tlX+18,tlY+8},  {tlX+24,tlY+8}},
{{tlX,tlY+12}, {tlX+6,tlY+12}, {tlX+12,tlY+12}, {tlX+18,tlY+12}, {tlX+24,tlY+12}},
{{tlX,tlY+16}, {tlX+6,tlY+16}, {tlX+12,tlY+16}, {tlX+18,tlY+16}, {tlX+24,tlY+16}},
};

/* Main function, implements the game in minimal functions */
void main(int argc, char *argv[]){
	strcpy_s(dev_name, argv[1]);
	strcpy_s(text_to_send, "s20");

	openSerial();
	Sleep(5000);
	serialSend();
	Sleep(10000);

	system("cls");
	resizeWindow();
	drawBoard();
	fillBoard();

	runGame();
	closeSerial();


	_getch();
}

/* Draws the playing board */
void drawBoard(){
	setColour(WHITE,BLACK);
	// Draws outline and squares
	int j;
	 for(j=cornerY+1; j<cornerY+20; j++){
	  gotoxy(cornerX,j);
	  printf("|     |     |     |     |     |");
	 }
	 gotoxy(cornerX,cornerY);
	 printf("|=============================|");
	 gotoxy(cornerX,cornerY+4);
	 printf("|-----------------------------|");
	 gotoxy(cornerX,cornerY+8);
	 printf("|-----------------------------|");
	 gotoxy(cornerX,cornerY+12);
	 printf("|-----------------------------|");
	 gotoxy(cornerX,cornerY+16);
	 printf("|-----------------------------|");
	 gotoxy(cornerX,cornerY+20);
	 printf("|=============================|");
	 // Draws row and column identification IDs
	 setColour(TEAL,BLACK);
	 gotoxy(cornerX+3,cornerY-1);
	 printf("A     B     C     D     E");
	 int barCount = 0;
	 int sideNumbers[5] = {1,2,3,4,5};

	 for(int i = cornerY+2; i <= cornerY+20; i += 4){
		 gotoxy(cornerX-1,i);
		printf("%d", sideNumbers[barCount]);
		barCount++;
	 }
}

/* Fills the playing board with relevant pieces */
void fillBoard(){
	for(int i = 0; i < 5; i++) { // Scans every row
		for(int j = 0; j < 5; j++) { // Scans every column
			int pieceVal;
			pieceVal = BOARD_ARRAY[i][j];
			 switch (pieceVal){
			  case 0:// Is empty
				gotoSquare(i,j);
				printf(" ");
			   break;
			  case 1: // Is white
				setColour(YELLOW,BLACK);
				gotoSquare(i,j);
				printf("O");
			   break;
			  case 2: // Is black
				gotoSquare(i,j);
				setColour(RED,BLACK);
				printf("O");
				break;
			  case 3: // Is white king			
				setColour(YELLOW,BLACK);
<<<<<<< HEAD
=======
				printf("O");
				break;
			  case 3: // Is white king
				setColour(RED,BLACK);
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
				gotoSquare(i,j);
				printf("@");
			   break;
			  case 4: // Is black king
				gotoSquare(i,j);
<<<<<<< HEAD
				setColour(RED,BLACK);
=======
				setColour(YELLOW,BLACK);
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
				printf("@");
				break;
			  default:
				gotoSquare(i,j);
			 }
		}
	}
}

/* Highlights the inputted piece with a red ring 
 * h = Highlight
 * r = Remove
*/
void highlightPiece(int row, int column, char operation){
	setColour(RED,BLACK);

	COORD pieceCoord = BOARD_COORDS[row][column];
	int x = pieceCoord.X;
	int y = pieceCoord.Y;

	// Highlight
	if (operation == 'h'){
	gotoxy(x-1,y-1);printf("+"); gotoxy(x,y-1);printf("-"); gotoxy(x+1,y-1);printf("+");

	gotoxy(x-1,y);printf("|");	/*    Piece is here      */	gotoxy(x+1,y);printf("|");

	gotoxy(x-1,y+1);printf("+"); gotoxy(x,y+1);printf("-"); gotoxy(x+1,y+1);printf("+");
	}
	// Remove
	else if (operation == 'r'){
	gotoxy(x-1,y-1);printf(" "); gotoxy(x,y-1);printf(" "); gotoxy(x+1,y-1);printf(" ");

	gotoxy(x-1,y);printf(" ");	/*    Piece is here      */	gotoxy(x+1,y);printf(" ");

	gotoxy(x-1,y+1);printf(" "); gotoxy(x,y+1);printf(" "); gotoxy(x+1,y+1);printf(" ");
	}
}

/* Sets cursor to text or error locations
 * t = Text
 * e = Error
 * d = Debug
 */

void setCursor(char type){
	// Text
	if (type == 't') {
		gotoxy(cornerX, cornerY+22);
		printf("                                               ");
		gotoxy(cornerX, cornerY+22);
	} 
	// Error
	else if (type == 'e'){
		gotoxy(cornerX, cornerY+24);
		printf("                                               ");
		gotoxy(cornerX, cornerY+24);
	}
	// Debug
	else if (type == 'd'){
		gotoxy(cornerX, cornerY+26);
		printf("                                               ");
		gotoxy(cornerX, cornerY+26);
		setColour(CYAN,BLACK);
	}
}

/* Gets user input for piece and decodes to useable value for BOARD_ARRAY */
void selectPiece(){

	char selectedPiece[] = "xx";

	setColour(WHITE,BLACK);
	setCursor('t');
	printf("Select Piece: ");
	scanf_s("%2s", selectedPiece, 3);

	realPiece[0] = selectedPiece[0]-49;	// Row
	realPiece[1] = selectedPiece[1]-97; // Column
}

/* Checks the selected piece is valid / movable by the user i.e White / 1 */
int checkPiece(int row, int column, char userType){

	int pieceVal = BOARD_ARRAY[row][column];
	if (userType == 'p'){
		if (pieceVal == 1 || pieceVal == 3){
			setCursor('e'); // Clear error
			highlightPiece(realPiece[0], realPiece[1], 'h');
			return 1;
		}
		else{
			setColour(RED,BLACK);
			setCursor('e');
			printf("Invalid piece");
			highlightPiece(realPiece[0], realPiece[1], 'r');
			return 0;
		}
	}
	else if (userType == 'c'){
		if (pieceVal == 2 || pieceVal == 4){
			setCursor('e'); // Clear error
			highlightPiece(realPiece[0], realPiece[1], 'h');
			return 1;
		}
		else{
			setColour(RED,BLACK);
			setCursor('e');
			printf("Invalid piece");
			highlightPiece(realPiece[0], realPiece[1], 'r');
			return 0;
		}
<<<<<<< HEAD
=======
	
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
	}
}

/* Gets user input for move and decodes to useable value for BOARD_ARRAY */
void selectMove(){

	char selectedMove[] = "xx";

	setColour(WHITE,BLACK);
	setCursor('t');
	printf("Select Move: ");
	scanf_s("%2s", selectedMove, 3);

	realMove[0] = selectedMove[0]-49;	// Row
	realMove[1] = selectedMove[1]-97;	// Column

}

/* Checks the selected move is valid and do-able 
 * 0 = Invalid move
 * 1 = Valid move 1 space backwards
 * -1 = Valid move 1 space fowards
 * -20 = Valid move jump foward left
 * -21 = Valid move jump foward right
 * 20 = Valid move jump backwards left
 * 21 = Valid move jump backwards right
 * 9 = Restart piece selection
*/
int checkMove(int row, int column){

	int pieceVal = BOARD_ARRAY[row][column];
	int squareColour = BOARD_COLOURS[row][column];

	int moveDiffR = realMove[0]-realPiece[0];
	int moveDiffC = realMove[1]-realPiece[1];

	setCursor('e');
	highlightPiece(realMove[0], realMove[1], 'h');

	// Same piece is selected
	if ((realMove[0] == realPiece[0]) && (realMove[1] == realPiece[1])){
		return 9;
	}

	// Check square is empty
	if (pieceVal == 0){
		// Check square is white
		if (squareColour == 1){
			// Check move is not sideways or upwards
			if ((moveDiffC != 0) || (moveDiffR != 0)){
				// Check move is jump or single move
				if( (abs(moveDiffC) <= 2) && (abs(moveDiffR) <= 2)){

					/* Move is valid, what type of move? */
					// Jump foward and left
					if ((moveDiffR == -2) && (moveDiffC == -2)){
						if ((BOARD_ARRAY[row+1][column+1] == 2) || BOARD_ARRAY[row+1][column+1] == 4){
							return -20;
						}
						else{
							setColour(RED,BLACK);
							setCursor('e');
							printf("Invalid move - Jumped piece is not opponents");
							highlightPiece(realMove[0], realMove[1], 'r');
							return 0;
						}
					}

					// Jump foward and right
					if ((moveDiffR == -2) && (moveDiffC == 2)){
						if ((BOARD_ARRAY[row+1][column-1] == 2) || BOARD_ARRAY[row+1][column-1] == 4){
							return -21;
						}
						else{
							setColour(RED,BLACK);
							setCursor('e');
<<<<<<< HEAD
							printf("Invalid move - Jumped piece is not opponents");
=======
							printf("Invalid move");
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
							highlightPiece(realMove[0], realMove[1], 'r');
							return 0;
						}
					}

					// Jump backwards and left
					if ((moveDiffR == 2) && (moveDiffC == -2)){
						// isKing?
<<<<<<< HEAD
						if (BOARD_ARRAY[realPiece[0]][realPiece[1]] == 3){
							if ((BOARD_ARRAY[row-1][column+1] == 2) || BOARD_ARRAY[row-1][column+1] == 4){
								return 20;
=======
						if (pieceVal == 3){
							if ((BOARD_ARRAY[row-1][column+1] == 2) || BOARD_ARRAY[row-1][column+1] == 4){
								return 20;
							}
							else{
								setColour(RED,BLACK);
								setCursor('e');
								printf("Invalid move");
								highlightPiece(realMove[0], realMove[1], 'r');
								return 0;
							}
						}
						else{
							setColour(RED,BLACK);
							setCursor('e');
							printf("Invalid move");
							highlightPiece(realMove[0], realMove[1], 'r');
							return 0;
						}
					}

					// Jump backwards and right
					if ((moveDiffR == 2) && (moveDiffC == 2)){
						// isKing?
						if (pieceVal == 3){
							if ((BOARD_ARRAY[row-1][column-1] == 2) || BOARD_ARRAY[row-1][column-1] == 4){
								return 21;
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
							}
							else{
								setColour(RED,BLACK);
								setCursor('e');
								printf("Invalid move - Jumped piece is not opponents");
								highlightPiece(realMove[0], realMove[1], 'r');
								return 0;
							}
						}
						else{
							setColour(RED,BLACK);
							setCursor('e');
							printf("Invalid move - Not king (Back Left)");
							highlightPiece(realMove[0], realMove[1], 'r');
							return 0;
						}
					}

					// Jump backwards and right
					if ((moveDiffR == 2) && (moveDiffC == 2)){
						// isKing?
						if (BOARD_ARRAY[realPiece[0]][realPiece[1]] == 3){
							if ((BOARD_ARRAY[row-1][column-1] == 2) || BOARD_ARRAY[row-1][column-1] == 4){
								return 21;
							}
							else{
								setColour(RED,BLACK);
								setCursor('e');
								printf("Invalid move - Jumped piece is not opponents");
								highlightPiece(realMove[0], realMove[1], 'r');
								return 0;
							}
						}
						else{
							setColour(RED,BLACK);
							setCursor('e');
							printf("Invalid move - Not king (Back Right)");
							highlightPiece(realMove[0], realMove[1], 'r');
							return 0;
						}
					}

					// Normal foward move
					if (moveDiffR == -1){
						return 1;
					}

					// Normal backward move
					if (moveDiffR == 1){
<<<<<<< HEAD
						if (BOARD_ARRAY[realPiece[0]][realPiece[1]] == 3){
=======
						if (pieceVal == 3){
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
							return -1;
						}
						else{
							setColour(RED,BLACK);
							setCursor('e');
							printf("Invalid move - Not king (Back Move)");
							highlightPiece(realMove[0], realMove[1], 'r');
							return 0;
						}
					}
				}
				else{
					setColour(RED,BLACK);
					setCursor('e');
					printf("Invalid move - Move difference > 2");
					highlightPiece(realMove[0], realMove[1], 'r');
					return 0;
				}
			}
			else{
				setColour(RED,BLACK);
				setCursor('e');
				printf("Invalid move - Move difference 0");
				highlightPiece(realMove[0], realMove[1], 'r');
				return 0;
			}
		}
		else{
			setColour(RED,BLACK);
			setCursor('e');
			printf("Invalid move - Not valid colour square");
			highlightPiece(realMove[0], realMove[1], 'r');
			return 0;
		}
	}
	else{
		setColour(RED,BLACK);
		setCursor('e');
		printf("Invalid move - Not empty square");
		highlightPiece(realMove[0], realMove[1], 'r');
		return 0;
	}
}

/* Moves the selected piece - jumpSize codes:
 * 1 = Valid move 1 space backward
 * -1 = Valid move 1 space foward
 * -20 = Valid move jump foward left
 * -21 = Valid move jump foward right
 * 20 = Valid move jump backwards left
 * 21 = Valid move jump backwards right
 */
void movePiece(int realPieceR, int realPieceC, int realMoveR, int realMoveC, int jumpSize){
	highlightPiece(realMove[0], realMove[1], 'r');
	highlightPiece(realPiece[0], realPiece[1], 'r');

	// Store current value
	int pieceVal = BOARD_ARRAY[realPieceR][realPieceC];
	// Set old piece to empty square
	BOARD_ARRAY[realPieceR][realPieceC] = 0;
	// Set new piece to old piece value
	BOARD_ARRAY[realMoveR][realMoveC] = pieceVal;

	// Clear jumped piece
	if (jumpSize == -20){ // Foward left
		BOARD_ARRAY[realMoveR+1][realMoveC+1] = 0;
	}
	else if (jumpSize == -21){ // Foward right
		BOARD_ARRAY[realMoveR+1][realMoveC-1] = 0;
	}
	else if (jumpSize == 20){ // Backwards left
		BOARD_ARRAY[realMoveR-1][realMoveC+1] = 0;
	}
	else if (jumpSize == 21){ // Backwards right
		BOARD_ARRAY[realMoveR-1][realMoveC-1] = 0;
	}
<<<<<<< HEAD
=======

	fillBoard();
}

/* Runs the game, runs turns and checks for win */
void runGame(){
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce

	if (BOARD_ARRAY[realMoveR][realMoveC] == 1){
		if (realMoveR == 0){
			BOARD_ARRAY[realMoveR][realMoveC] = 3;
		}
	}

	if (BOARD_ARRAY[realMoveR][realMoveC] == 2){
		if (realMoveR == 4){
			BOARD_ARRAY[realMoveR][realMoveC] = 4;
		}
	}
	fillBoard();
}

void arduinoMovePiece(int realPieceR, int realPieceC, int realMoveR, int realMoveC){
	char sendString[5];
	int dir = 1;
	sprintf_s(sendString, "q%d%d%d", realPieceR, realPieceC, dir);
	strcpy_s(text_to_send, sendString);
	serialSend();

	Sleep(5000);

	dir = 0;
	sprintf_s(sendString, "q%d%d%d", realPieceR, realPieceC, dir);
	strcpy_s(text_to_send, sendString);
	serialSend();

	Sleep(5000);

	dir = 1;
	sprintf_s(sendString, "q%d%d%d", realMoveR, realMoveC, dir);
	strcpy_s(text_to_send, sendString);
	serialSend();

	Sleep(5000);

	dir = 0;
	sprintf_s(sendString, "q%d%d%d", realMoveR, realMoveC, dir);
	strcpy_s(text_to_send, sendString);
	serialSend();
}

/* Runs the player turn */
void playerTurn(){
	setCursor('d');
	printf("Player turn - Start"); 

<<<<<<< HEAD
	// Drive board to player
	char sendString[5];
	sprintf_s(sendString, "q%d%d%d", 8, 8, 8);
	strcpy_s(text_to_send, sendString);
	serialSend();

=======
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
	start:
	int checkMoveReturn = 100;

	do{
		selectPiece();
		checkPiece(realPiece[0], realPiece[1], 'p');
	}
	while(checkPiece(realPiece[0], realPiece[1], 'p') == 0);

	do{
		selectMove();
		checkMoveReturn = checkMove(realMove[0], realMove[1]);
	}
	while(checkMoveReturn == 0);

	switch(checkMoveReturn){
	case 9: // Restart piece selection
		highlightPiece(realMove[0], realMove[1], 'r');
		highlightPiece(realPiece[0], realPiece[1], 'r');
		setCursor('d');
		printf("Player turn - Restart"); 
		goto start;
		break;
	case 1: // Backwards move
		movePiece(realPiece[0], realPiece[1], realMove[0], realMove[1], 1);
		break;
	case -1: // Foward move
		movePiece(realPiece[0], realPiece[1], realMove[0], realMove[1], -1);
		break;
	case -20: // Foward left
		movePiece(realPiece[0], realPiece[1], realMove[0], realMove[1], -20);
		break;
	case -21: // Foward right
		movePiece(realPiece[0], realPiece[1], realMove[0], realMove[1], -21);
		break;
	case 20: // Backwards left
		movePiece(realPiece[0], realPiece[1], realMove[0], realMove[1], 20);
		break;
	case 21: // Backwards right
		movePiece(realPiece[0], realPiece[1], realMove[0], realMove[1], 21);
		break;
	}
	setCursor('d');
	printf("Player turn - End"); 
<<<<<<< HEAD

	sprintf_s(sendString, "q%d%d%d", 9,9,9);
	strcpy_s(text_to_send, sendString);
	serialSend();
	Sleep(3000);
}

/* Runs the Computers turn */
int compTurn(){
	setCursor('d');
	printf("Comp turn - Start"); 
	for(int x = 0; x<4; x++){
		printf("\n                                                                                ");
	}
	setCursor('d');

	Sleep(2000);
	struct move compMoves[48];
	int pieceVal = 0;
	int moveID = 0;

	// Calculates all possible moves for each piece
	for(int row = 0; row <5; row++){
		for(int col = 0; col <5; col++){
			pieceVal = BOARD_ARRAY[row][col];
			// Black piece
			if (pieceVal == 2){
				/* Moves */
				if (BOARD_ARRAY[row+1][col-1] == 0 && row+1 < 5 && col-1 > -1){
					// empty sqaure - valid move down and left
					compMoves[moveID].origin[0] = row;
					compMoves[moveID].origin[1] = col;
					compMoves[moveID].moveTo[0] = row+1;
					compMoves[moveID].moveTo[1] = col-1;
					compMoves[moveID].jumpSize = 1;
					moveID++;
					printf("\n1 - (%d,%d) > (%d,%d)",row, col, row+1, col-1);
				}
				if (BOARD_ARRAY[row+1][col+1] == 0 && row+1 < 5 && col+1 < 5){
					// empty square - valid move down and right
					compMoves[moveID].origin[0] = row;
					compMoves[moveID].origin[1] = col;
					compMoves[moveID].moveTo[0] = row+1;
					compMoves[moveID].moveTo[1] = col+1;
					compMoves[moveID].jumpSize = 1;
					moveID++;
					printf("\n2 - (%d,%d) > (%d,%d)",row, col, row+1, col+1);
				}
				/* Jumps */
				if (BOARD_ARRAY[row+1][col-1] == 1 || BOARD_ARRAY[row+1][col-1] == 3){
					if (BOARD_ARRAY[row+2][col-2] == 0 && row+2 < 5 && col-2 > -1){
						// empty square - valid jump down and left
						compMoves[moveID].origin[0] = row;
						compMoves[moveID].origin[1] = col;
						compMoves[moveID].moveTo[0] = row+2;
						compMoves[moveID].moveTo[1] = col-2;
						compMoves[moveID].jumpSize = 20;
						moveID++;
						printf("\n3 - (%d,%d) > (%d,%d)",row, col, row+2, col-2);
					}
				}
				if (BOARD_ARRAY[row+1][col+1] == 1 || BOARD_ARRAY[row+1][col+1] == 3){
					if (BOARD_ARRAY[row+2][col+2] == 0 && row+2 < 5 && col+2 < 5){
						// empty square - valid jump down and right
						compMoves[moveID].origin[0] = row;
						compMoves[moveID].origin[1] = col;
						compMoves[moveID].moveTo[0] = row+2;
						compMoves[moveID].moveTo[1] = col+2;
						compMoves[moveID].jumpSize = 21;
						moveID++;
						printf("\n4 - (%d,%d) > (%d,%d)",row, col, row+2, col+2);
					}
				}
			}
			// Black king
			if (pieceVal == 4){
				/* Moves */
				if (BOARD_ARRAY[row+1][col-1] == 0 && row+1 < 5 && col-1 > -1){
					// empty sqaure - valid move down and left
					compMoves[moveID].origin[0] = row;
					compMoves[moveID].origin[1] = col;
					compMoves[moveID].moveTo[0] = row+1;
					compMoves[moveID].moveTo[1] = col-1;
					compMoves[moveID].jumpSize = 1;
					moveID++;
					printf("\n5 - (%d,%d) > (%d,%d)",row, col, row+1, col-1);
				}
				if (BOARD_ARRAY[row+1][col+1] == 0 && row+1 < 5 && col+1 < 5){
					// empty square - valid move down and right
					compMoves[moveID].origin[0] = row;
					compMoves[moveID].origin[1] = col;
					compMoves[moveID].moveTo[0] = row+1;
					compMoves[moveID].moveTo[1] = col+1;
					compMoves[moveID].jumpSize = 1;
					moveID++;
					printf("\n6 - (%d,%d) > (%d,%d)",row, col, row+1, col-1);
				}
				if (BOARD_ARRAY[row-1][col-1] == 0 && row-1 > -1 && col-1 > -1){
					// empty sqaure - valid move up and left
					compMoves[moveID].origin[0] = row;
					compMoves[moveID].origin[1] = col;
					compMoves[moveID].moveTo[0] = row-1;
					compMoves[moveID].moveTo[1] = col-1;
					compMoves[moveID].jumpSize = -1;
					moveID++;
					printf("\n7 - (%d,%d) > (%d,%d)",row, col, row-1, col-1);
				}
				if (BOARD_ARRAY[row-1][col+1] == 0 && row-1 > -1 && col+1 < 5){
					// empty square - valid move up and right
					compMoves[moveID].origin[0] = row;
					compMoves[moveID].origin[1] = col;
					compMoves[moveID].moveTo[0] = row-1;
					compMoves[moveID].moveTo[1] = col+1;
					compMoves[moveID].jumpSize = -1;
					moveID++;
					printf("\n8 - (%d,%d) > (%d,%d)",row, col, row-1, col+1);
				}
				/* Jumps */
				if (BOARD_ARRAY[row+1][col-1] == 1 || BOARD_ARRAY[row+1][col-1] == 3){
					if (BOARD_ARRAY[row+2][col-2] == 0 && row+2 < 5 && col-2 > -1){
						// empty square - valid jump down and left
						compMoves[moveID].origin[0] = row;
						compMoves[moveID].origin[1] = col;
						compMoves[moveID].moveTo[0] = row+2;
						compMoves[moveID].moveTo[1] = col-2;
						compMoves[moveID].jumpSize = 20;
						moveID++;
						printf("\n9 - (%d,%d) > (%d,%d)",row, col, row+2, col-2);
					}
				}
				if (BOARD_ARRAY[row+1][col+1] == 1 || BOARD_ARRAY[row+1][col+1] == 3){
					if (BOARD_ARRAY[row+2][col+2] == 0 && row+2 < 5 && col+2 < 5){
						// empty square - valid jump down and right
						compMoves[moveID].origin[0] = row;
						compMoves[moveID].origin[1] = col;
						compMoves[moveID].moveTo[0] = row+2;
						compMoves[moveID].moveTo[1] = col+2;
						compMoves[moveID].jumpSize = 21;
						moveID++;
						printf("\na - (%d,%d) > (%d,%d)",row, col, row+2, col+2);
					}
				}
				if (BOARD_ARRAY[row-1][col-1] == 1 || BOARD_ARRAY[row-1][col-1] == 3){
					if (BOARD_ARRAY[row-2][col-2] == 0 && row-2 > -1 && col-2 > -1){
						// empty square - valid jump up and left
						compMoves[moveID].origin[0] = row;
						compMoves[moveID].origin[1] = col;
						compMoves[moveID].moveTo[0] = row-2;
						compMoves[moveID].moveTo[1] = col-2;
						compMoves[moveID].jumpSize = -20;
						moveID++;
						printf("\nb - (%d,%d) > (%d,%d)",row, col, row-2, col-2);
					}
				}
				if (BOARD_ARRAY[row-1][col+1] == 1 || BOARD_ARRAY[row-1][col+1] == 3){
					if (BOARD_ARRAY[row-2][col+2] == 0 && row-2 > -1 && col+2 < 5){
						// empty square - valid jump up and right
						compMoves[moveID].origin[0] = row;
						compMoves[moveID].origin[1] = col;
						compMoves[moveID].moveTo[0] = row-2;
						compMoves[moveID].moveTo[1] = col+2;
						compMoves[moveID].jumpSize = -21;
						moveID++;
						printf("\nc - (%d,%d) > (%d,%d)",row, col, row-2, col+2);
					}
				}
			}
		}
	}

	// Pick a random move ID
	srand(time(NULL));
	if(moveID != 0){
		int movePick = rand() % moveID;
		printf("\nEx - %d", movePick);
		movePiece(compMoves[movePick].origin[0], compMoves[movePick].origin[1], compMoves[movePick].moveTo[0], compMoves[movePick].moveTo[1], compMoves[movePick].jumpSize);
		arduinoMovePiece(compMoves[movePick].origin[0], compMoves[movePick].origin[1], compMoves[movePick].moveTo[0], compMoves[movePick].moveTo[1]);
	}

	return moveID;
}

/* Runs the game, runs turns and checks for win */
void runGame(){

	int blackPieces = 5;
	int whitePieces = 5;
	int compMoves = 0;

	while(blackPieces != 0 || whitePieces != 0){
		for(int i = 0; i < 5; i++) { // Scans every row
			for(int j = 0; j < 5; j++) { // Scans every column
				if (BOARD_ARRAY[i][j] == 1 || BOARD_ARRAY[i][j] == 3){
					whitePieces++;
				}
				if (BOARD_ARRAY[i][j] == 2 || BOARD_ARRAY[i][j] == 4){
					blackPieces++;
				}
			}
		}
		playerTurn();
		compMoves = compTurn();
	}

	if (blackPieces == 0 || compMoves == 0){
		setCursor('t');
		printf("You won!");
	}
	if (whitePieces == 0){
		setCursor('t');
		printf("You lost!");
	}
}

int openSerial(){

	// Open the specified serial port (first command line argument)
	fprintf(stderr, "Opening serial port %s...", dev_name);
	hSerial = CreateFileA(dev_name, GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial==INVALID_HANDLE_VALUE){
		fprintf(stderr, "Error\n");
		return 1;
	}
	fprintf(stderr, "OK\n");
 
	// Set device parameters (38400 baud, 1 start bit, 1 stop bit, no parity)
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (GetCommState(hSerial, &dcbSerialParams) == 0){
		fprintf(stderr, "Error getting device state\n");
		CloseHandle(hSerial);
		return 1;
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if(SetCommState(hSerial, &dcbSerialParams) == 0){
		fprintf(stderr, "Error setting device parameters\n");
		CloseHandle(hSerial);
		return 1;
	}
 
	// Set COM port timeout settings
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if(SetCommTimeouts(hSerial, &timeouts) == 0){
		fprintf(stderr, "Error setting timeouts\n");
		CloseHandle(hSerial);
		return 1;
	}
}

int serialSend(){
	char text_recieved[MAX_PATH];
	// Send specified text (second command line argument cannot contain spaces)
	setCursor('d');
	fprintf(stderr, "\nSending text: %s\n", text_to_send);
	if(!WriteFile(hSerial, text_to_send, strlen(text_to_send), &dwBytesWritten, NULL)){
		fprintf(stderr, "Error writing text to %s\n", dev_name);
	}
	else{
		fprintf(stderr, "%d bytes written to %s\n",
				dwBytesWritten, dev_name);
	}

	ReadFile(hSerial, text_recieved, 30, &dwBytesRead, NULL);
	fprintf(stdout, "Recieved Text: %c\n", text_recieved[0]);
	fprintf(stderr, "%d bytes read %s\n", dwBytesRead, dev_name);
	// exit normally
	return 0;
}

int closeSerial(){
		// Close serial port
	fprintf(stderr, "Closing serial port...");
	if (CloseHandle(hSerial) == 0){
		fprintf(stderr, "Error\n", dev_name);
		return 1;
	}
	fprintf(stderr, "OK\n");
}
=======
}


/* Runs the Computers turn */
void compTurn(){
	setCursor('d');
	printf("Comp turn - Start"); 

	int checkMoveReturn = 100;

	do{
		// Select random piece
		checkPiece(realPiece[0], realPiece[1], 'c');
	}
	while(checkPiece(realPiece[0], realPiece[1], 'c') == 0);

	do{
		// Select move for piece
		checkMoveReturn = checkMove(realMove[0], realMove[1]);
	}
	while(checkMoveReturn == 0);

	// Valid move 1 space
	if (checkMoveReturn == 1 || checkMoveReturn == -1){
		movePiece(realPiece[0], realPiece[1],realMove[0], realMove[1], 1);
	}
	// Valid move 2 jump
	else if (checkMoveReturn == 2){
		movePiece(realPiece[0], realPiece[1],realMove[0], realMove[1], 2);
	}
	// Valid move 2 jump backwards
	else if (checkMoveReturn == -2){
		movePiece(realPiece[0], realPiece[1],realMove[0], realMove[1], -2);
	}

	/*
	FUNCTION_FIND_ALL_LEGAL_MOVES( BOARD_ARRAY ) Returns: array ALL_LEGAL_MOVES
	FUNCTION_FIND_BEST_MOVE( BOARD_ARRAY, ALL_LEGAL_MOVES ) Returns: array MY_MOVE
	FUNCTION_DO_MOVE( BOARD_ARRAY, MY_MOVE ) Throws: error ILLEGAL_MOVE Updates: MY_BOARD
	repeat from start for each turn
	*/
}
>>>>>>> daa8560609d7b5d27c8b1cec3d7ce83760f17fce
