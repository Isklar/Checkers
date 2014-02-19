#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>

/* Function prototypes */
// Utilities
COORD getCoord(int, int);
void gotxy(int, int);
void gotoSquare(int, int);
void resizeWindow();
void setColour(const int, const int);
// Gameplay
void drawBoard();
void fillBoard();
void runGame();
void playerTurn();
void compTurn();

void highlightPiece(int, int, char);
void selectPiece();
int checkPiece(int, int, char);
int checkMove(int, int);
void movePiece(int, int, int, int, int);

/* Global variable initialisation */
COORD coord={0,0};

// Top left corner of board
int cornerX = 15;	// Horizontal
int cornerY = 2;	// Vertical
// Top left X and Y
int tlX = cornerX + 3;
int tlY = cornerY + 2;


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
int BOARD_ARRAY[6][6] = 
{
{0, 2, 0, 2, 0, 2},
{2, 0, 2, 0, 2, 0},
{0, 0, 0, 0, 0, 0},
{0, 0, 4, 0, 0, 0},
{0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 0},
};

/* Global square colours | 1 - white | 2 - black [ROW][COLUMN] */
const int BOARD_COLOURS[6][6] = 
{
{2, 1, 2, 1, 2, 1 },
{1, 2, 1, 2, 1, 2 },
{2, 1, 2, 1, 2, 1 },
{1, 2, 1, 2, 1, 2 },
{2, 1, 2, 1, 2, 1 },
{1, 2, 1, 2, 1, 2 },
};

/* Screen coordinates of every board square [ROW][COLUMN]*/
COORD BOARD_COORDS[6][6] = 
{
{{tlX,tlY},    {tlX+6,tlY},    {tlX+12,tlY},    {tlX+18,tlY},    {tlX+24,tlY},    {tlX+30,tlY}},
{{tlX,tlY+4},  {tlX+6,tlY+4},  {tlX+12,tlY+4},  {tlX+18,tlY+4},  {tlX+24,tlY+4},  {tlX+30,tlY+4}},
{{tlX,tlY+8},  {tlX+6,tlY+8},  {tlX+12,tlY+8},  {tlX+18,tlY+8},  {tlX+24,tlY+8},  {tlX+30,tlY+8}},
{{tlX,tlY+12}, {tlX+6,tlY+12}, {tlX+12,tlY+12}, {tlX+18,tlY+12}, {tlX+24,tlY+12}, {tlX+30,tlY+12}},
{{tlX,tlY+16}, {tlX+6,tlY+16}, {tlX+12,tlY+16}, {tlX+18,tlY+16}, {tlX+24,tlY+16}, {tlX+30,tlY+16}},
{{tlX,tlY+20}, {tlX+6,tlY+20}, {tlX+12,tlY+20}, {tlX+18,tlY+20}, {tlX+24,tlY+20}, {tlX+30,tlY+20}},
};

/* Main function, implements the game in minimal functions */
void main(){
	system("cls");
	resizeWindow();
	drawBoard();
	fillBoard();

	runGame();

	_getch();
}

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

/* Draws the playing board */
void drawBoard(){
	setColour(WHITE,BLACK);
	// Draws outline and squares
	int j;
	 for(j=cornerY+1; j<cornerY+24; j++){
	  gotoxy(cornerX,j);
	  printf("|     |     |     |     |     |     |");
	 }
	 gotoxy(cornerX,cornerY);
	 printf("|===================================|");
	 gotoxy(cornerX,cornerY+4);
	 printf("|-----------------------------------|");
	 gotoxy(cornerX,cornerY+8);
	 printf("|-----------------------------------|");
	 gotoxy(cornerX,cornerY+12);
	 printf("|-----------------------------------|");
	 gotoxy(cornerX,cornerY+16);
	 printf("|-----------------------------------|");
	 gotoxy(cornerX,cornerY+20);
	 printf("|-----------------------------------|");
	 gotoxy(cornerX,cornerY+24);
	 printf("|===================================|");
	 // Draws row and column identification IDs
	 setColour(TEAL,BLACK);
	 gotoxy(cornerX+3,cornerY-1);
	 printf("A     B     C     D     E     F");
	 int barCount = 0;
	 int sideNumbers[6] = {1,2,3,4,5,6};

	 for(int i = cornerY+2; i <= 24; i += 4){
		 gotoxy(cornerX-1,i);
		printf("%d", sideNumbers[barCount]);
		barCount++;
	 }
}

/* Fills the playing board with relevant pieces */
void fillBoard(){
	for(int i = 0; i < 6; i++) { // Scans every row
		for(int j = 0; j < 6; j++) { // Scans every column
			int pieceVal;
			pieceVal = BOARD_ARRAY[i][j];
			 switch (pieceVal){
			  case 0:// Is empty
				gotoSquare(i,j);
				printf(" ");
			   break;
			  case 1: // Is white
				setColour(RED,BLACK);
				gotoSquare(i,j);
				printf("O");
			   break;
			  case 2: // Is black
				gotoSquare(i,j);
				setColour(YELLOW,BLACK);
				printf("O");
				break;
			  case 3: // Is white king
				setColour(RED,BLACK);
				gotoSquare(i,j);
				printf("@");
			   break;
			  case 4: // Is black king
				gotoSquare(i,j);
				setColour(YELLOW,BLACK);
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
		gotoxy(cornerX, cornerY+26);
		printf("                                ");
		gotoxy(cornerX, cornerY+26);
	} 
	// Error
	else if (type == 'e'){
		gotoxy(cornerX, cornerY+28);
		printf("                                ");
		gotoxy(cornerX, cornerY+28);
	}
	// Debug
	else if (type == 'd'){
		gotoxy(cornerX, cornerY+36);
		printf("                                ");
		gotoxy(cornerX, cornerY+36);
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

	setCursor('e'); // Clear error
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
							printf("Invalid move");
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
							printf("Invalid move");
							highlightPiece(realMove[0], realMove[1], 'r');
							return 0;
						}
					}

					// Jump backwards and left
					if ((moveDiffR == 2) && (moveDiffC == -2)){
						// isKing?
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

					// Normal foward move
					if (moveDiffR == -1){
						return 1;
					}

					// Normal backward move
					if (moveDiffR == 1){
						if (pieceVal == 3){
							return -1;
						}
						else{
							setColour(RED,BLACK);
							setCursor('e');
							printf("Invalid move");
							highlightPiece(realMove[0], realMove[1], 'r');
							return 0;
						}
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
	else{
		setColour(RED,BLACK);
		setCursor('e');
		printf("Invalid move");
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
	// Removes all highlighting
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

	fillBoard();
}

/* Runs the game, runs turns and checks for win */
void runGame(){

	//char turn = 'p'; // Will be c or p depending on Computer or Player turn
	playerTurn();
	/*
	do{
	playerturn();
	}
	while ( turn == p)
	*/

}

/* Runs the player turn */
void playerTurn(){
	//setCursor('d');
	//printf("Player turn - Start"); 

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
	case 9: // Restart piece go
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
	_getch();

	/*
	FUNCTION_FIND_ALL_LEGAL_MOVES( BOARD_ARRAY ) Returns: array ALL_LEGAL_MOVES
	FUNCTION_FIND_BEST_MOVE( BOARD_ARRAY, ALL_LEGAL_MOVES ) Returns: array MY_MOVE
	FUNCTION_DO_MOVE( BOARD_ARRAY, MY_MOVE ) Throws: error ILLEGAL_MOVE Updates: MY_BOARD
	repeat from start for each turn
	*/

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
}
