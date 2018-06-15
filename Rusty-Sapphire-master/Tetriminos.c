
#include <stdlib.h>
#include <stdio.h>

#include "Tetris.h"

/**
 * Creates a tetrimino according to its type 
 * */
Tetrimino* createTetrimino(short type) {
	
	Tetrimino* tetrimino = malloc(sizeof(Tetrimino));
	
	tetrimino->type = type;
	
	int i, j;
	for(i=0; i<TETRI_SIZE; i++)
		for(j=0; j<TETRI_SIZE; j++)
			tetrimino->array[i][j] = 0;
		
	switch(type) {
		case TETRI_O:
			rotateO(tetrimino, ROT_0);
		break;
		
		case TETRI_J:
			rotateJ(tetrimino, ROT_0);
		break;
		
		case TETRI_L:
			rotateL(tetrimino, ROT_0);
		break;
		
		case TETRI_I:
			rotateI(tetrimino, ROT_0);
		break;
		
		case TETRI_Z:
			rotateZ(tetrimino, ROT_0);
		break;
		
		case TETRI_S:
			rotateS(tetrimino, ROT_0);
		break;
		
		case TETRI_T:
			rotateT(tetrimino, ROT_0);
		break;
		
		default:
		break;
	}
	return tetrimino;
}

/** 
 * Rotates a Tetrimino 
 * */
void rotate(Tetrimino* tet, short rotation) {
	short i, j ;
	
	for(i=0; i<TETRI_SIZE; i++)
		for(j=0; j<TETRI_SIZE; j++)
			tet->array[i][j] = 0;
			
	switch(tet->type) {
		case TETRI_O:
			rotateO(tet, rotation);
		break;
			
		case TETRI_J:
			rotateJ(tet, rotation);
		break;
		
		case TETRI_L:
			rotateL(tet, rotation);
		break;
		
		case TETRI_I:
			rotateI(tet, rotation);
		break;
		
		case TETRI_Z:
			rotateZ(tet, rotation);
		break;
		
		case TETRI_S:
			rotateS(tet, rotation);
		break;
		
		case TETRI_T:
			rotateT(tet, rotation);
		break;
		
		default:
		break;
	}
}

/**
 * Rotates a O Tetrimino 
 * */
void rotateO(Tetrimino* tetrimino, short rotation) {
	switch(rotation) {
		case ROT_0:
		case ROT_1:
		case ROT_2:
		case ROT_3:
			tetrimino->array[3][0] = 1;
			tetrimino->array[3][1] = 1;
			tetrimino->array[2][0] = 1;
			tetrimino->array[2][1] = 1;
		break;
		
		default:
		break;
	}
}

/**
 * Rotates a J Tetrimino 
 * */
void rotateJ(Tetrimino* tetrimino, short rotation) {
	switch(rotation) {
		case ROT_0:
			tetrimino->array[3][0] = 1;
			tetrimino->array[3][1] = 1;
			tetrimino->array[2][1] = 1;
			tetrimino->array[1][1] = 1;
		break;
		
		case ROT_1:
			tetrimino->array[2][0] = 1;
			tetrimino->array[2][1] = 1;
			tetrimino->array[2][2] = 1;
			tetrimino->array[3][2] = 1;
		break;
		
		case ROT_2:
			tetrimino->array[1][0] = 1;
			tetrimino->array[1][1] = 1;
			tetrimino->array[2][0] = 1;
			tetrimino->array[3][0] = 1;
		break;
		
		case ROT_3:
			tetrimino->array[2][0] = 1;
			tetrimino->array[3][0] = 1;
			tetrimino->array[3][1] = 1;
			tetrimino->array[3][2] = 1;
		break;
		
		default:
		break;
	}
}

/**
 * Rotates a L Tetrimino 
 * */
void rotateL(Tetrimino* tetrimino, short rotation) {
	switch(rotation) {
		case ROT_0:
			tetrimino->array[1][0] = 1;
			tetrimino->array[2][0] = 1;
			tetrimino->array[3][0] = 1;
			tetrimino->array[3][1] = 1;
		break;
		
		case ROT_1:
			tetrimino->array[3][0] = 1;
			tetrimino->array[3][1] = 1;
			tetrimino->array[3][2] = 1;
			tetrimino->array[2][2] = 1;
		break;
		
		case ROT_2:
			tetrimino->array[1][0] = 1;
			tetrimino->array[1][1] = 1;
			tetrimino->array[2][1] = 1;
			tetrimino->array[3][1] = 1;
		break;
		
		case ROT_3:
			tetrimino->array[3][0] = 1;
			tetrimino->array[2][0] = 1;
			tetrimino->array[2][1] = 1;
			tetrimino->array[2][2] = 1;
		break;
		
		default:
		break;
	}
}

/**
 * Rotates a I Tetrimino 
 * */
void rotateI(Tetrimino* tetrimino, short rotation) {
	switch(rotation) {
		case ROT_0:
		case ROT_2:
			tetrimino->array[0][0] = 1;
			tetrimino->array[1][0] = 1;
			tetrimino->array[2][0] = 1;
			tetrimino->array[3][0] = 1;
		break;
		
		case ROT_1:
		case ROT_3:
			tetrimino->array[3][0] = 1;
			tetrimino->array[3][1] = 1;
			tetrimino->array[3][2] = 1;
			tetrimino->array[3][3] = 1;
		break;
		
		default:
		break;
	}
}

/**
 * Rotates a Z Tetrimino 
 * */
void rotateZ(Tetrimino* tetrimino, short rotation) {
	switch(rotation) {
		case ROT_0:
		case ROT_2:
			tetrimino->array[2][0] = 1;
			tetrimino->array[3][0] = 1;
			tetrimino->array[1][1] = 1;
			tetrimino->array[2][1] = 1;
		break;
		
		case ROT_1:
		case ROT_3:
			tetrimino->array[2][0] = 1;
			tetrimino->array[2][1] = 1;
			tetrimino->array[3][1] = 1;
			tetrimino->array[3][2] = 1;
		break;
		
		default:
		break;
	}
}

/**
 * Rotates a S Tetrimino 
 * */
void rotateS(Tetrimino* tetrimino, short rotation) {
	switch(rotation) {
		case ROT_0:
		case ROT_2:
			tetrimino->array[1][0] = 1;
			tetrimino->array[2][0] = 1;
			tetrimino->array[2][1] = 1;
			tetrimino->array[3][1] = 1;
		break;
		
		case ROT_1:
		case ROT_3:
			tetrimino->array[2][1] = 1;
			tetrimino->array[2][2] = 1;
			tetrimino->array[3][0] = 1;
			tetrimino->array[3][1] = 1;
		break;
		
		default:
		break;
	}
}

/**
 * Rotates a T Tetrimino 
 * */
void rotateT(Tetrimino* tetrimino, short rotation) {
	switch(rotation) {
		case ROT_0:
			tetrimino->array[2][1] = 1;
			tetrimino->array[3][0] = 1;
			tetrimino->array[3][1] = 1;
			tetrimino->array[3][2] = 1;
		break;
		
		case ROT_1:
			tetrimino->array[2][0] = 1;
			tetrimino->array[1][1] = 1;
			tetrimino->array[2][1] = 1;
			tetrimino->array[3][1] = 1;
		break;
		
		case ROT_2:
			tetrimino->array[2][0] = 1;
			tetrimino->array[2][1] = 1;
			tetrimino->array[2][2] = 1;
			tetrimino->array[3][1] = 1;
		break;
		
		case ROT_3:
			tetrimino->array[1][0] = 1;
			tetrimino->array[2][0] = 1;
			tetrimino->array[3][0] = 1;
			tetrimino->array[2][1] = 1;
		break;
		
		default:
		break;
	}
}

/**
 * Displays a Tetrmino
 * */
void displayTetrimino(Tetrimino* tetrimino) {
	int i, j;
	for(i=0; i<TETRI_SIZE; i++) {
		for(j=0; j<TETRI_SIZE; j++) {
			if(tetrimino->array[i][j] == 1)
				printf("O");
			else
				printf("_");
		}
		printf("\n");
	}
}

/**
 * Frees a Tetrimino 
 * */
void freeTetrimino(Tetrimino* tetrimino) {
	free(tetrimino);
}


