/*
 * tetris.h
 *
 *  Created on: 2018. 5. 15.
 *      Author: kny
 */

#ifndef TETRIS_H_
#define TETRIS_H_

/* Libs */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <float.h>
//#include "audio.h"

/* Expension factor of shapes */
#define EXP_FACT 2

/* Frame dimension */
#define FRAMEW 23
#define FRAMEH 20
#define FRAMEW_NB 18
#define FRAMEH_NB 8

/* Shapes position */
#define N_POS ((current.pos < 3) ? current.pos + 1 : 0)
#define P_POS ((current.pos > 0) ? current.pos - 1 : 3)

/** Coefficient to apply to a cleared line */
#define ROW_VALUE_COEFF 10

/** Number fo coefficients for Genetic ALgorithm */
#define COEF_NB 4

/* Draw the score.. */
#define DRAW_SCORE() set_color(Score);                              \
     printf("\033[%d;%dH %d", FRAMEH_NB + 2, FRAMEW + 10, level);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 3, FRAMEW + 10, score);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 4, FRAMEW + 10, lines);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 12, FRAMEW + 10, lifes);   \
     set_color(0);

/*
#define DRAW_SCORE_ai() set_color(Score);                              \
     printf("\033[%d;%dH %d", FRAMEH_NB + 2, FRAMEW + 60, level);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 3, FRAMEW + 60, score);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 4, FRAMEW + 60, lines);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 12, FRAMEW + 60, lifes);   \
     set_color(0);
*/

/* Bool type */
typedef enum { False, True } Bool;

/* Shape structure */
typedef struct
{
     int num;
     int next;
     int pos;
     int x, y;
     Bool last_move;
} shape_t;

typedef struct
{
	int x,y;
	int pos;
	float heu;
} move;

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
void frame_init(int, int);
void frame_nextbox_init(int, int);
void frame_refresh(int, int);
void frame_preview(int, int);
void frame_nextbox_refresh(int, int);

/* shapes.c */
void shape_set(void);
void shape_unset(void);
void shape_new(int, int);
void shape_go_down(int, int);
void shape_set_position(int);
void shape_move(int);
void shape_drop(void);
void block_down(void);
void revive(void);

/* tetris.c */
char* first(char * name);
void init(void);
void init_ai(void);
void arrange_score(int l);
void check_plain_line(int, int);
int check_possible_pos(int, int);
void get_key_event(void);
void quit(char * name, int, int);
void ai_quit(int, int);
void music(const char * filename, int len);
void sound(const char * filename, int len);

/* ai.c */
void AI_shape_go_down(float *coefs); //AI_shape_go_down
float heuristic(float* coefs);
int countHoles();
int computeTotalHeight();
int countCompleteLines();
int maxHeight();
int computeHollowness();
int maxColumnHeight(int columnNb);

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
int buf;
float bestMoveHeu;

Bool running;
//Bool running2;

#endif /* TETRIS_H_ */
