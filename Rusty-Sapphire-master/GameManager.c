#include <stdlib.h>
#include <stdio.h>
#include "Tetris.h"

/** 
 * Randomizes a tetrimino
 * */
short tetriminoNumberGenerator() {
	return rand()%7;
}

/** 
 * Randomly generates a pieces file
 * */
void generatePiecesFile(int size) {
	FILE* f = fopen("pieces", "w");
	int i;
	for(i=0; i<size; i++)
		fprintf(f, "%d\n", tetriminoNumberGenerator());
	fclose(f);
}

/** 
 * Randomly generates a moves file
 * */
void generateMovesFile(int size) {
	FILE* f = fopen("moves", "w");
	int i;
	for(i=0; i<size; i++)
		fprintf(f, "%d,%d\n", rand()%7, rand()%4);
	fclose(f);
}

/** 
 * Plays one move in the game
 * */
short playAMove(Game* game, Tetrimino* tet, short x, short rotation) {
	
	rotate(tet, rotation);
	
	short value;
	value = addTetrimino(game, tet, x);
	
	/* If not added, return */
	if(value == ERROR)
		return ERROR;
	
	/* If added, score + 1 and score + coeff * rows deleted */
	game->score++;
	value = removeRows(game);
	game->score += ROW_VALUE_COEFF * value;
	return value;
}

/** 
 * Reads a file of pieces
 * */
int readPiecesFile(char* filename, short* piecesArray, int maxReadableSize) {
	FILE* f = NULL;
	f = fopen(filename, "r");
	if(f == NULL)
		return ERROR;
	
	int number;
	char ch;
	int sizeRead = 0;
	
	while(sizeRead < maxReadableSize) {
		ch = fgetc(f);
		if(ch == EOF)
			break;
		number =  ch - '0';
		
		ch = fgetc(f);
		if(ch == EOF)
			break;
		piecesArray[sizeRead] = number;
		sizeRead++;
	}
	
	fclose(f);
	
	return sizeRead;
}

/** 
 * reads a moves file
 * */
int readMovesFile(char* filename, Move* movesArray, int maxReadableSize) {
	FILE* f = NULL;
	f = fopen(filename, "r");
	if(f == NULL)
		return ERROR;
	
	int number;
	char ch;
	int sizeRead = 0;
	
	while(sizeRead < maxReadableSize) {
		/* reading x */
		ch = fgetc(f);
		if(ch == EOF)
			break;
		number =  ch - '0';
		movesArray[sizeRead].x = number;
		
		/* reading coma */
		ch = fgetc(f);
		if(ch == EOF)
			break;
			
		/* Reading rotation */
		ch = fgetc(f);
		if(ch == EOF)
			break;
		number = ch - '0';
		movesArray[sizeRead].rotation = number;
		
		/* reading CR */
		ch = fgetc(f);
		if(ch == EOF)
			break;
			
		printf("%d, %d\n", movesArray[sizeRead].x, movesArray[sizeRead].rotation);
		/* Increasing size */
		sizeRead++;
	}
	
	fclose(f);
	
	return sizeRead;
}

/** 
 * Plays a complete game without AI 
 * */
int playAGame(int numberOfTetriminos, short* piecesArray, int piecesSize, Move* movesArray, int movesSize) {
	if(numberOfTetriminos <= 0)
		return ERROR;
		
	Game* game = createGame();
	Tetrimino* tet;
	short added;
	short counter = 0;
	
	do {
		
		if(piecesArray == NULL) 	
			tet = createTetrimino(tetriminoNumberGenerator()); /* Using generator if no array  */
		else
			tet = createTetrimino(piecesArray[counter]); /* Using array otherwise */
		
		
		if(movesArray == NULL) 
			added = playAMove(game, tet, rand()%6, rand()%4); /* Using random position and rotation if no array */
		else
			added = playAMove(game, tet, movesArray[counter].x, movesArray[counter].rotation); /* Using moves array otherwise */
		
		displayGameBoard(game);
		
		numberOfTetriminos--;
		counter++;
		
		freeTetrimino(tet);
		
		
	} while(numberOfTetriminos > 0 && added >= 0);
	
	short score = game->score;
	freeGame(game);
	
	return score;
}

