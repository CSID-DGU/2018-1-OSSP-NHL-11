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
#define N_POS ((current1.pos < 3) ? current1.pos + 1 : 0)
#define P_POS ((current1.pos > 0) ? current1.pos - 1 : 3)

/** Coefficient to apply to a cleared line */
#define ROW_VALUE_COEFF 10

/** Number fo coefficients for Genetic ALgorithm */
#define COEF_NB 4

/* Draw the score.. */
#define DRAW_SCORE1() set_color(Score);                              \
     printf("\033[%d;%dH %d", FRAMEH_NB + 2, FRAMEW + 10, level1);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 3, FRAMEW + 10, score1);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 4, FRAMEW + 10, lines1);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 12, FRAMEW + 10, lifes1);   \
     set_color(0);

#define DRAW_SCORE2() set_color(Score);                              \
     printf("\033[%d;%dH %d", FRAMEH_NB + 2, FRAMEW + 10, level2);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 3, FRAMEW + 10, score2);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 4, FRAMEW + 10, lines2);   \
     printf("\033[%d;%dH %d", FRAMEH_NB + 12, FRAMEW + 10, lifes2);   \
     set_color(0);

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

/* frame_user.c */
void frame_init_user(void);
void frame_nextbox_init_user(void);
void frame_refresh_user(void);
void frame_preview_user(void);
void frame_nextbox_refresh_user(void);

/* shapes_user.c */
void shape_set_user(void);
void shape_unset_user(void);
void shape_new_user(void);
void shape_go_down_user(void);
void shape_set_position_user(int);
void shape_move_user(int);
void shape_drop_user(void);
void block_down_user(void);
void revive_user(void);

/* tetris_user.c */
char* first(char * name);
void init_user(void);
void arrange_score_user(int l);
void check_plain_line_user(void);
int check_possible_pos_user(int, int);
void get_key_event_user(void);
void quit_user(char * name);

/* frame_ai.c */
void frame_init_ai(int, int);
void frame_nextbox_init_ai(int, int);
void frame_refresh_ai(int, int);
void frame_preview_ai(int, int);
void frame_nextbox_refresh_ai(int, int);

/* shapes_ai.c */
void shape_set_ai(void);
void shape_unset_ai(void);
void shape_new_ai(int, int);
void shape_set_position_ai(int);
void block_down_ai(void);

/* tetris_user.c */
char* first(char * name);
void init_user(void);
void arrange_score_user(int l);
void check_plain_line_user(void);
int check_possible_pos_user(int, int);
void get_key_event(void);
void quit_user(char * name);
void playUser();

/* tetris_ai.c */
void init_ai(void);
void arrange_score_ai(int l);
void check_plain_line_ai(void);
int check_possible_pos_ai(int, int);
void quit_ai();
void playAI();

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
/* * * * * *
 * GLOBALS
 * * * * * */

const int shapes1[10][4][5][2];
const int shapes2[10][4][5][2];
struct itimerval tv;
struct termios back_attr;

//user variables
int score1;
int lines1;
int level1;
int lifes1;
shape_t current1;
int frame1[FRAMEH + 1][FRAMEW + 1];
int frame_nextbox1[FRAMEH_NB][FRAMEW_NB];

//ai variables
int score2;
int lines2;
int level2;
int lifes2;
shape_t current2;
int frame2[FRAMEH + 1][FRAMEW + 1];
int frame_nextbox2[FRAMEH_NB][FRAMEW_NB];
int buf;
float bestMoveHeu;

Bool running1;
Bool running2;
Bool finish1;
Bool finish2;
