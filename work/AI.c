#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "tetris.h"

/**
 * Plays a complete game using the AI
 * */
unsigned long long playAIGame(short* piecesArray, unsigned long long piecesSize, float* coefs) {
	
	Game* game = createGame();
	Game* copy;
	Move move;
	Tetrimino* tet;
	unsigned long long indexArray = 0;
	short added;
	unsigned long long score;
	int piecesAdded = 0;
	
	FILE* f = fopen("moves", "w");
	
	do {
		copy = copyGame(game);
		move = determineMove(copy, DEPTH, piecesArray, indexArray, piecesSize, coefs);
		fprintf(f, "%d,%d\n", move.x, move.rotation);
		freeGame(copy);
		tet = createTetrimino(piecesArray[indexArray++]);
		
		if(DISPLAY) {
			displayGameBoard(game);
			printf("Score: %llu, number of pieces: %d\n", game->score, piecesAdded);
		}
		
		added = playAMove(game, tet, move.x, move.rotation);
		piecesAdded++;
		freeTetrimino(tet);
		
	} while(added != ERROR && indexArray < piecesSize);
	
	displayGameBoard(game);
	printf("Score: %llu, number of pieces: %d\n", game->score, piecesAdded);
	
	score = game->score;
	freeGame(game);
	
	/* Fill the moves file with 0 to reach the desired length */
	while(indexArray < piecesSize) {
		fprintf(f, "0,0\n");
		indexArray++;
	}
	fclose(f);
	
	return score;
}


/**
 * Determines the next move to play using Depth-First Limited Search
 * */
Move determineMove(Game* game, short depth, short* tetList, unsigned long long indexList, unsigned long long tetSize, float* coefs) {
	if (depth < 1 || indexList >= tetSize) {
		Move move;
		move.heuristic = heuristic(game, coefs);
		return move;
	}
	
	short i;
	short added;
	Move move, bestMove;
	Tetrimino* tet = createTetrimino(tetList[indexList]);
	Game* copy;
	
	Move moves[40];
	short movesLength = possibleMoves(game, tet, moves);
	
	bestMove.x = 0;
	bestMove.rotation = 0;
	bestMove.heuristic = -FLT_MAX;
	
	for(i=0; i<movesLength; i++) { // For every possible moves
			
			copy = copyGame(game); // Copy a Game
			
			removeRows(copy); // removing rows for previously added tetrimino 
			
			rotate(tet, moves[i].rotation);
			
			added = addTetrimino(copy, tet, moves[i].x); // add the tetrimino
			
			
			if(added == 1) { // tetrimino added
				move = determineMove(copy, depth-1, tetList, indexList+1, tetSize, coefs);				
			}

			if(added == 1 && move.heuristic > bestMove.heuristic) {
				bestMove.heuristic = move.heuristic;
				bestMove.rotation = moves[i].rotation;;
				bestMove.x = moves[i].x;
			}
			
			freeGame(copy); // Delete copy
	}
	
	freeTetrimino(tet); // Free created tetrimino 
	
	return bestMove;
}

/** 
 * Returns the size of the array containing the different possible moves to apply to this game state to this particular tetrimino */
short possibleMoves(Game* game, Tetrimino* tet, Move* moves) {
	short i, j, counter = 0;
	short maxX = maxTetX(tet);
	switch(tet->type) {
		case TETRI_O:
			for(i=0; i<T_WIDTH - maxX; i++) {
				moves[counter].x = i;
				moves[counter++].rotation = ROT_0;
			}
			return counter;
		break;
		
		case TETRI_I:
		case TETRI_S:
		case TETRI_Z:
			for(j=ROT_0; j<=ROT_1; j++) {
				for(i=0; i<T_WIDTH - maxX; i++) {
					moves[counter].x = i;
					moves[counter++].rotation = j;
				}
			}
			return counter;
		break;
		
		case TETRI_J:
		case TETRI_L:
		case TETRI_T:
		for(j=ROT_0; j<=ROT_3; j++) {
				for(i=0; i<T_WIDTH - maxX; i++) {
					moves[counter].x = i;
					moves[counter++].rotation = j;
				}
			}
			return counter;
		break;
		
		default:
			return 0;
		break;
	}
}

/**
 * Returns a heuristic for the current game board
 * */
float heuristic(Game* game, float* coefs) {
	float rows = coefs[0];
	float height = coefs[1];
	float holes = coefs[2];
	float hollowness = coefs[3];
	float heuristicValue = 0.0;
	heuristicValue += holes * countHoles(game);
	heuristicValue += height * computeTotalHeight(game);
	heuristicValue += rows * countCompleteLines(game);
	heuristicValue += hollowness * computeHollowness(game);
	return heuristicValue;
}

/**
 * Returns the number of full lines
 * */
short countCompleteLines(Game* game) {
	short i, j;
	short counter = 0, rowCounter = 0;
	short gameHeight = maxHeight(game);
	
	for(i=T_HEIGHT-1; i>=gameHeight; i--) {
		j=0;
		counter = 0;
		while(getBitboardValue(game->array[i], j) !=0 && j < T_WIDTH) {
			j++;
			counter++;
		}
		
		if(counter == T_WIDTH)
			rowCounter++;
	}
	return rowCounter;
}

/**
 * Returns the number of holes
 * */
short countHoles(Game* game) {
	short i, j, k, counter;
	short totalCounter = 0;
	for(i=TETRI_SIZE+1; i<T_HEIGHT; i++) {
		for(j=0; j<T_WIDTH; j++) {
			if(getBitboardValue(game->array[i], j) == 0 && getBitboardValue(game->array[i-1], j) == 1) {	// if case is empty and the case above is filled
				counter = 0;
				k = i;
				while(getBitboardValue(game->array[k], j) == 0 && k<T_HEIGHT-1) {			// while the case is empty and going toward the bottom
					counter++;
					k++;
				}
				k--;
				if(getBitboardValue(game->array[k+1], j) == 1) 							// if next case filled, adding to total number
					totalCounter += counter;
			}
		}
	}
	
	return totalCounter;
}

/**
 * Returns the total height of the game
 * */
short computeTotalHeight(Game* game) {
	short height = 0;
	short i, j;
	
	for(j=0; j<T_WIDTH; j++) {
		for(i=TETRI_SIZE; i<T_HEIGHT; i++)
			if(getBitboardValue(game->array[i], j) == 1) // case filled
				height += (T_HEIGHT - i);
	}
	return height;
}

/**
 * Returns the summation of heights' differences between columns
 * */
short computeHollowness(Game* game) {
	short i;
	short summation = 0;
	short maxHeight[T_WIDTH];
	
	for(i=0; i<T_WIDTH; i++) {
		maxHeight[i] = maxColumnHeight(game, i);
	}
	
	for(i=0; i<T_WIDTH-1; i++)
		summation += abs(maxHeight[i] - maxHeight[i+1]);
		
	return summation;
}

/**
 * Returns the maximum height of a given column
 * */
short maxColumnHeight(Game* game, short columnNb) {
	if(columnNb < 0 || columnNb >= T_WIDTH)
		return ERROR;
	short i;
	for(i=TETRI_SIZE; i<T_HEIGHT; i++) {
		if(getBitboardValue(game->array[i], columnNb) == 1)
			return (T_HEIGHT - i);
	}
	return 0;
}

