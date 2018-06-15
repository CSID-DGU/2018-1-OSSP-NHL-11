#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tetris.h"

float DEFAULT_COEFS[COEF_NB] = {
	0.820999,
	-0.024000,
	-0.581000,
	-0.155000,
};


int main(void) {
		
	srand(time(NULL));
	
	/* Generates a file of pieces called "pieces" */
	generatePiecesFile(LENGTH);
	
	/* Reads the pieces file */
	short piecesArray[LENGTH];
	unsigned long long piecesSize = readPiecesFile("pieces", piecesArray, LENGTH);
		
	/* Plays a game using the AI using the pieces file */
	//unsigned long long score = playAIGame(piecesArray, piecesSize, DEFAULT_COEFS);
	//printf("Game finished with score %llu\n", score);
	
	/* Runs the genetic algorithm */
	geneticAlgorithm(GENETIC_GENERATIONS_NB, GENETIC_GAMES_NB, GENETIC_PIECES_LENGTH);
	
	/* Runs the hill climbing algorithm */
	//hillClimbing();

}

