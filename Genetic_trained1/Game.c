#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tetris.h"

/**
 * Creates a game
 * */
Game* createGame() {
    Game* game = malloc(sizeof(Game));
    game->score = 0;

    short i;
    for(i=0; i<T_HEIGHT; i++) {
        game->array[i] = 0;
    }
    return game;
}

/**
 * Copy a Game
 * */
Game* copyGame(Game* game) {
    Game* copy = createGame();
    copy->score = game->score;

    short i;
    for(i=0; i<T_HEIGHT; i++)
        copy->array[i] = game->array[i];
    return copy;
}

/**
 * Adds a tetrimino to the game (without score modification)
 * */
short addTetrimino(Game* game, Tetrimino* tet, short x) {
    if(x < 0 || x >= T_WIDTH)
        return -1;
    if(x + maxTetX(tet) >= T_WIDTH)
        return -1;


    short y = 0;
    /* As long as it can do further */
    while(canGoDown(game, x, y, tet))
        y++;

    if((maxTetY(tet) + y) < TETRI_SIZE) {
        return -1;
    }


    short i, j;
    for(i=0; i<TETRI_SIZE; i++) {
        for(j=0; j<TETRI_SIZE; j++) {
            if(tet->array[i][j] != 0)
                game->array[i+y] = setBitboardValue(game->array[i+y], j+x, 1);
        }
    }
    return 1;
}

/**
 * Determines whether a tetrimino can go further in the board
 * */
short canGoDown(Game* game, short x, short y, Tetrimino* tet) {
    short i, j;

    for(i = TETRI_SIZE-1; i>=0; i--)
        for(j=0; j<TETRI_SIZE; j++)
            if(tet->array[i][j] == 1) // if the tetrimino has a block on a case
                if(y+i+1 >= T_HEIGHT || getBitboardValue(game->array[y+i+1], x+j) == 1) // testing if the game's array has no more room where its gonna be
                    return 0;
    return 1;
}

/**
 * Removes full rows
 * */
short removeRows(Game* game) {
    short i, j, k, l;
    short counter = 0, rowCounter = 0;
    short gameHeight = maxHeight(game);

    for(i=T_HEIGHT-1; i>=gameHeight; i--) {
        j=0;
        counter = 0;
        while(getBitboardValue(game->array[i], j) !=0 && j < T_WIDTH) {
            j++;
            counter++;
        }

        if(counter == T_WIDTH) {
            rowCounter++;

            for(k=i; k>=gameHeight-1; k--) {
                for(l=0; l<T_WIDTH; l++)
                    game->array[k] = setBitboardValue(game->array[k], l, getBitboardValue(game->array[k-1], l));
            }
            i++; // incrementing i because all went one case down
        }
    }
    return rowCounter;
}

/**
 * Returns the maximum height of the game
 * */
short maxHeight(Game* game) {
    short i, j;
    for(i=0; i<T_HEIGHT; i++)
        for(j=0; j<T_WIDTH; j++)
            if(getBitboardValue(game->array[i], j) != 0) {
                return i;
            }
    return 0;
}

/**
 * Returns the maximum y index of a Tetrimino
 * */
short maxTetY(Tetrimino* tet) {
    int i, j;

    for(i = 0; i<TETRI_SIZE; i++)
        for(j = 0; j<TETRI_SIZE; j++)
            if(tet->array[i][j] != 0)
                return i;
    return TETRI_SIZE;
}

/**
 * Returns the x position of the upper left case of a tetrimino
 * */
short tetUpperLeftCase(Tetrimino* tet) {
    int i;
    for(i=0; i<TETRI_SIZE; i++)
            if(tet->array[i][0] != 0)
                return i;
    return TETRI_SIZE;
}

/**
 * Returns the maximum x index of a Tetrimino
 * */
short maxTetX(Tetrimino* tet) {
    int i, j;

    for(j = TETRI_SIZE-1; j>=0; j--)
        for(i = 0; i < TETRI_SIZE; i++)
            if(tet->array[i][j] == 1)
                return j;
    return 0;
}

/**
 * Displays the game
 * */
void displayGameBoard(Game* game) {
    short i, j;
    printf("############\n");
    for(i=TETRI_SIZE; i<T_HEIGHT; i++) {
        printf("#");
        for(j=0; j<T_WIDTH; j++) {
            if(getBitboardValue(game->array[i], j) != 0)
                printf("X");
            else
                printf(" ");
       }
        printf("#");
        printf("\n");
    }
    printf("############\n");
}

/**
 * Frees a Game
 * */
void freeGame(Game* game) {
    free(game);
}

