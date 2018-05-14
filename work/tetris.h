/*
*      tetris.h
*      Copyright © 2008 Martin Duquesnoy <xorg62@gmail.com>
*      All rights reserved.
*
*      Redistribution and use in source and binary forms, with or without
*      modification, are permitted provided that the following conditions are
*      met:
*
*      * Redistributions of source code must retain the above copyright
*        notice, this list of conditions and the following disclaimer.
*      * Redistributions in binary form must reproduce the above
*        copyright notice, this list of conditions and the following disclaimer
*        in the documentation and/or other materials provided with the
*        distribution.
*      * Neither the name of the  nor the names of its
*        contributors may be used to endorse or promote products derived from
*        this software without specific prior written permission.
*
*      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Libs */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <string.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include "audio.h"

/* Number fo Generations for Genetic Algorithm */
#define GENETIC_GENERATIONS_NB 100
/* Number fo Generations for Genetic Algorithm */
#define GENETIC_GAMES_NB 10
/* Number of pieces per game */
#define GENETIC_PIECES_LENGTH 10000
/* Number fo coefficients for Genetic ALgorithm */
#define COEF_NB 4
/* Number fo individuals in a population */
#define GENES_NB 100 // generation하는 횟수(세대 수)
/* Mutation factor */
#define MUT_FACTOR 0.05

/* Expension factor of shapes */
#define EXP_FACT 2

/* Board Height */
#define T_HEIGHT 24
/* Board Width */
#define T_WIDTH 10

/* Size of a Tetrimino */
#define TETRI_SIZE 4
/* Default number of rotations */
#define T_ROTATION 4

/* Error code */
#define ERROR -1

/* Default depth of Depth-First Search */
#define DEPTH 2

/* If set to 1, display the game board for every move played, if set to 0, displays only the final game board */
#define DISPLAY 1

/* Frame dimension */
#define FRAMEW 23
#define FRAMEH 20
#define FRAMEW_NB 18
#define FRAMEH_NB 8

/* Defines the precision of heuristic's coefficients */
#define PRECISION 0.001 

/* Shapes position */
#define N_POS ((current.pos < 3) ? current.pos + 1 : 0)
#define P_POS ((current.pos > 0) ? current.pos - 1 : 3)

/* Size of a Tetrimino */
#define TETRI_SIZE 4
/* Default number of rotations */
#define T_ROTATION 4

/* Constants for Tetriminos */
#define TETRI_O 0
#define TETRI_J 1
#define TETRI_L 2
#define TETRI_I 3
#define TETRI_Z 4
#define TETRI_S 5
#define TETRI_T 6

/* Contsants for rotations */
#define ROT_0 0
#define ROT_1 1
#define ROT_2 2
#define ROT_3 3

/* Draw the score.. */
#define DRAW_SCORE() set_color(Score);                              \
     printf("\033[%d;%dH %d", FRAMEH_NB + 2, FRAMEW + 10, level);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 3, FRAMEW + 10, score);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 4, FRAMEW + 10, lines);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 12, FRAMEW + 10, lifes);   \
     set_color(0);

/* Bool type */
typedef enum { False, True } Bool;

/* Gene Structure */
typedef struct Gene {
 float coefs[COEF_NB];
 int score;
 float fitness;
} Gene;

/* Population Structure */
typedef struct Population {
 Gene genes[GENES_NB];
 short genesNumber;
} Population;

/* Game Structure */
typedef struct Game {
 unsigned short array[T_HEIGHT];
 unsigned long long score;
} Game;

/* Move Structure */
typedef struct Move {
 short x;
 short rotation;
 float heuristic;
} Move;

/* Tetrimino Structure */
typedef struct Tetrimino {
 short array[TETRI_SIZE][TETRI_SIZE];
 short type;
} Tetrimino;

/* Shape structure */
typedef struct
{
 int num;
 int next;
 int pos;
 int x, y;
 Bool last_move;
} shape_t;

/* Color enum */
enum { Black, Blue, Red, Magenta, White, Green, Cyan, Yellow, Test, Test_2, Test_3, Border, Score, ColLast };

/* Prototypes */

/* util.c */
void clear_term(void);
void set_cursor(Bool);
void printxy(int, int, int, char*);
void set_color(int);
int nrand(int, int);
void sig_handler(int);

/* frame.c */
void frame_init(void);
void frame_nextbox_init(void);
void frame_refresh(void);
void frame_preview(void);
void frame_nextbox_refresh(void);

/* shapes.c */
void shape_set(void);
void shape_unset(void);
void shape_new(void);
void shape_go_down(void);
void shape_set_position(int);
void shape_move(int);
void shape_drop(void);
void block_down(void);
void revive(void);

/* tetris.c */
char* first(char * name);
void init(void);
void arrange_score(int l);
void check_plain_line(void);
int check_possible_pos(int, int);
void get_key_event(void);
void quit(char * name);
void music(const char * filename, int len);
void sound(const char * filename, int len);

/* Variables */
const int shapes[10][4][5][2];
struct itimerval tv;
struct termios back_attr;
shape_t current;
int frame[FRAMEH + 1][FRAMEW + 1];
int frame_nextbox[FRAMEH_NB][FRAMEW_NB];
int score;
int lines;
int level;
int lifes;

Bool running;

/* genetic.c */
float randomTenth(short lowerBound, short upperBound);
float randomFloat(short lowerBound, short upperBound);
Population* initialPopulation();
void fitness(Population* pop, short gamesNb, int piecesSize);
Population* nextPopulation(Population* parent, int piecesSize, short gamesNb);
void fitnessCalculation(Population* parent, int piecesSize, short gamesNb);
short selection(Population* parent);
void reproduction(Population* parent, Population* next, short parentA, short parentB, short child);
void mutation(Population* next, short genomeToMutate);
void geneticAlgorithm(short generationNb, short gamesNb, int piecesSize);
void printGeneCoefficients(FILE* file, Gene gene);
void printAllGenesCoefsAndFitness(FILE* file, Population* pop);
short searchBestGene(Population* pop);
short searchLowestFitness(Population* pop);


