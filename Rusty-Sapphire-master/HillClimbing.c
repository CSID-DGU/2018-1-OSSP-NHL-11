#include <stdio.h>
#include <stdlib.h>
#include "Tetris.h"

/**
 * Main function for the Hill Climbing algorithm
 * */
void hillClimbing() {
	short hillClimbed[COEF_NB] = {1, 1, 1, 1};
	short** pieces = malloc(HILL_CLIMBING_GAMES_NB * sizeof(short*));
	for(short j = 0; j<HILL_CLIMBING_GAMES_NB; j++)
		pieces[j] = malloc(HILL_CLIMBING_GAME_LENGTH * sizeof(short));
	
	/* No direction at the beginning */
	short directions[COEF_NB] = {0, 0, 0, 0};
	short i;
	
	int counter = 0;
	/* Initial coefficients, taken from results of genetic algorithm */
	float coefs[COEF_NB] = {0.78, -0.03, -0.55, -0.16};
	
	char filename[] = "HILL000.txt";
	FILE* f;
	
	do {
		/* Modifying the filename */
		filename[4] = counter/100 + '0';
		filename[5] = (counter/10)%10 + '0';
		filename[6] = counter%10 + '0';
		
		f = fopen(filename, "w");
		
		fprintf(f, "\nGlobal Climbing #%d\n\n", counter);
		printf("\nGlobal Climbing #%d\n\n", counter);
		
		/* Generate pieces (we keep the same pieces for hill climbing of each coef */
		for(i=0; i<HILL_CLIMBING_GAMES_NB; i++) {
			generatePiecesFile(HILL_CLIMBING_GAME_LENGTH);
			readPiecesFile("pieces", pieces[i], HILL_CLIMBING_GAME_LENGTH);
		}
		
		/* Perform a hill climbing for each coef */
		hillClimbed[0] = specificCoefHillClimbing(pieces, coefs, directions, 0, f);
		hillClimbed[1] = specificCoefHillClimbing(pieces, coefs, directions, 1, f);
		hillClimbed[2] = specificCoefHillClimbing(pieces, coefs, directions, 2, f);
		hillClimbed[3] = specificCoefHillClimbing(pieces, coefs, directions, 3, f);
		
		/* File writing */
		fprintf(f, "\nFinal Coefs:\n");
		for(i=0; i<COEF_NB; i++) {
			fprintf(f, "%f, ", coefs[i]);
			printf("%f, ", coefs[i]);
		}
		fprintf(f, "\n");
		printf("\n");
		fclose(f);
		
		counter ++;
		
	} while(hillClimbed[0] != 0 || hillClimbed[1] != 0 || hillClimbed[2] != 0 || hillClimbed[3] != 0); // continue while still progressing 
	
	for(short j=0; j<HILL_CLIMBING_GAMES_NB; j++)
		free(pieces[j]);
	free(pieces);
}

/** 
 * Executes a Hill Climbing only on 1 coefficient
 * */
short specificCoefHillClimbing(short** pieces, float* coefs, short* directions, short indexToHillClimb, FILE* f) {
	int previousScore = 0;
	int	nextScore = 0;
	int counter = 0;
	long globalScore = 0;
		
	directions[indexToHillClimb] = determineDirection(coefs, indexToHillClimb);
	
	/* No need to hill climb if direction stabilized */
	if(directions[indexToHillClimb] == 0)
		return 0;
	do {
		previousScore = nextScore;
		nextScore = 0;
		coefs[indexToHillClimb] += directions[indexToHillClimb] * 0.001;
		for(short i=0; i<HILL_CLIMBING_GAMES_NB; i++)
			nextScore += playAIGame(pieces[i], HILL_CLIMBING_GAME_LENGTH, coefs);
		globalScore += nextScore;
		printf("Coef %d, score %d, fitness %f\n", indexToHillClimb, nextScore, nextScore / (5.0 * HILL_CLIMBING_GAME_LENGTH * HILL_CLIMBING_GAMES_NB));
		counter++;
	} while(nextScore >= previousScore);
	
	/* Cancelling the loss of coefficient (if while loop ended, it's because it was a bad idea to change the coefficient one more time*/
	coefs[indexToHillClimb] -= directions[indexToHillClimb] * 0.001; 
	fprintf(f, "Coef %d, score %li, fitness %f\n", indexToHillClimb, globalScore, globalScore / (5.0 * HILL_CLIMBING_GAMES_NB * HILL_CLIMBING_GAME_LENGTH * counter));
	printf("Coef %d, score %li, fitness %f\n", indexToHillClimb, globalScore, globalScore / (5.0 * HILL_CLIMBING_GAMES_NB * HILL_CLIMBING_GAME_LENGTH * counter));
	return 1;
}


/**
 *  Determines whether it should increase, decrease or do nothing on a coefficient
 * */
short determineDirection(float* coefs, short indexToDetermine) {
	int scoreLeft = 0, scoreStay = 0, scoreRight = 0;
	short pieces[HILL_CLIMBING_GAMES_NB][HILL_CLIMBING_GAME_LENGTH];
	short i = 0;
	
	printf("Determining direction\n");
	generatePiecesFile(HILL_CLIMBING_GAME_LENGTH);
	readPiecesFile("pieces", pieces[i], HILL_CLIMBING_GAME_LENGTH);
		
	/* To the left */
	coefs[indexToDetermine] -= 0.001;
	scoreLeft = playAIGame(pieces[i], HILL_CLIMBING_GAME_LENGTH, coefs);
		
	/* No direction */
	coefs[indexToDetermine] += 0.001;
	scoreStay = playAIGame(pieces[i], HILL_CLIMBING_GAME_LENGTH, coefs);
		
	/* To the right */
	coefs[indexToDetermine] += 0.001;
	scoreRight = playAIGame(pieces[i], HILL_CLIMBING_GAME_LENGTH, coefs);
	
	/* Cancel previous modification */
	coefs[indexToDetermine] -= 0.001;
	
	if(scoreLeft >= scoreStay && scoreLeft > scoreRight)
		return -1;
	else if(scoreRight >= scoreStay && scoreRight > scoreLeft)
		return 1;
	else if(scoreStay > scoreLeft && scoreStay > scoreRight)
		return 0;
	else
		return(rand()%2==0?-1:1);
}


