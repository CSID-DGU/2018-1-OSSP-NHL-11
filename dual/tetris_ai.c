/*
 *      tetris.c TTY-TETRIS Main file.
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

#include "tetris.h"
#include "config.h"
  
float DEFAULT_COEFS[COEF_NB] = {
		0.694806, -0.597780, -0.940100, -0.386985
};


/* Functions */

void init_ai(void)
{
  
     struct sigaction siga;
     struct termios term;

     /* Clean term */
     clear_term();
     set_cursor(False);
     /* Init terminal (for non blocking & noecho getchar();
      이것을 위로 옮긴 이유는 처음부터 껌벅커서를 지우기 위해*/
     tcgetattr(STDIN_FILENO, &term);
     tcgetattr(STDIN_FILENO, &back_attr);
     term.c_lflag &= ~(ICANON|ECHO);
     tcsetattr(0, TCSANOW, &term);
    /*스타트함수를 init에 통합했다*/
     //set_cursor(False); //커서없애줌
 /*
     printxy(0, FRAMEH_NB + 2, FRAMEW + 3, "Score :");
     printxy(0, FRAMEH_NB + 3, FRAMEW + 3, "Lines :");
     printxy(0, FRAMEH_NB + 4, FRAMEW + 3, "Left  : ←"); 
     printxy(0, FRAMEH_NB + 5, FRAMEW + 3, "Right : →"); 
     printxy(0, FRAMEH_NB + 6, FRAMEW + 3, "Change: ↑");
     printxy(0, FRAMEH_NB + 7, FRAMEW + 3, "Down  : ↓"); 
     printxy(0, FRAMEH_NB + 8, FRAMEW + 3, "Drop  : Space Bar");
     printxy(0, FRAMEH_NB + 9, FRAMEW + 3, "Pause : p"); 
     printxy(0, FRAMEH_NB + 10, FRAMEW + 3, "Revive : r");
     printxy(0, FRAMEH_NB + 11, FRAMEW + 3, "Quit  : q");  
    //게임 시작하기 전에 안내를 한번 해줌
    
     clear_term(); //화면 지움*/
     /* Make rand() really random :) */
     srand(getpid());

     /* Init variables */

     score2 = 0;
      
	//true일 경우에 게임의 축이 되는 루프가 계속 돌아가고 false일 경우 루프가 break되고 quit함수가 호출되어 종료된다
     running2 = True;
     finish2 = False;
     current2.y = (FRAMEW / 2) - 1;
     current2.num = nrand(0, 7); //7가지블록랜덤
     current2.next = nrand(0, 7);//다음 블록의 종류를 정함

     /* Score(오른쪽에 표시되는 안내사항을 보여주는 */
     printxy(0, FRAMEH_NB + 1, FRAMEW + 3, "Level :");
     printxy(0, FRAMEH_NB + 2, FRAMEW + 3, "Score :");
     printxy(0, FRAMEH_NB + 3, FRAMEW + 3, "Lines :");
     printxy(0, FRAMEH_NB + 4, FRAMEW + 3, "Left  : ←"); 
     printxy(0, FRAMEH_NB + 5, FRAMEW + 3, "Right : →"); 
     printxy(0, FRAMEH_NB + 6, FRAMEW + 3, "Change: ↑");
     printxy(0, FRAMEH_NB + 7, FRAMEW + 3, "Down  : ↓"); 
     printxy(0, FRAMEH_NB + 8, FRAMEW + 3, "Drop  : Space Bar");
     printxy(0, FRAMEH_NB + 9, FRAMEW + 3, "Pause : p"); 
     printxy(0, FRAMEH_NB + 10, FRAMEW + 3, "Revive : r");
     printxy(0, FRAMEH_NB + 11, FRAMEW + 3, "Life : ");
     printxy(0, FRAMEH_NB + 12, FRAMEW + 3, "Quit  : q"); 
     DRAW_SCORE2();

     /* Init signal */
     sigemptyset(&siga.sa_mask);
     siga.sa_flags = 0;
     siga.sa_handler = sig_handler;
     sigaction(SIGALRM, &siga, NULL);
     sigaction(SIGTERM, &siga, NULL);
     sigaction(SIGINT,  &siga, NULL);
     sigaction(SIGSEGV, &siga, NULL);

     /* Init timer */
     tv.it_value.tv_usec = TIMING;
     sig_handler(SIGALRM);
 
     return;
}


void arrange_score_ai(int l)
{
     /* 클리어한 라인에따라 점수부여. 여기서 의문점이 5줄이상일때 에러가 발생하는지
     테트리스는 5줄이상 못깹니다.  */
     switch(l)
     {
     case 1: score2 += 40;   break; /* One line */
     case 2: score2 += 100;  break; /* Two lines */
     case 3: score2 += 300;  break; /* Three lines */
     case 4: score2 += 1200; break; /* Four lines */
     }

     
     if (score2 >=100)  //레벨 추가
      level2=2;
     if (score2 >=400)
      level2=3;
     if (score2 >=700)
      level2=4;
     if(score2 >= 1000)
      level2 =5;
     lines2 += l;

     DRAW_SCORE2();

     return;
}

void check_plain_line_ai(void)
{
/*if(SDL_Init(SDL_INIT_AUDIO) < 0)
    {
       exit;
    }
    */
     int i, j, k, f, c = 0, nl = 0;
     int x= 0, y=50;
     for(i = 1; i < FRAMEH; ++i)
     {
          for(j = 1; j < FRAMEW; ++j)
               if(frame2[i][j] == 0)
                    ++c;
          if(!c)
          {
               ++nl;
               //sound("pop.wav",400);
               for(k = i - 1; k > 1; --k)
                    for(f = 1; f < FRAMEW; ++f)
                         frame2[k + 1][f] = frame2[k][f];
          }
          c = 0;
     }
     arrange_score_ai(nl);
     frame_refresh_ai(x, y);

     return;
}

int check_possible_pos_ai(int x, int y)
{
     int i, j, c = 0;

     for(i = 0; i < 5; ++i)
          for(j = 0; j < EXP_FACT; ++j)
               if(frame2[x + shapes2[current2.num][current2.pos][i][0]]
                  [y + shapes2[current2.num][current2.pos][i][1] * EXP_FACT + j] != 0)
                    ++c;

     return c;
}

void quit_ai() {
    char end;
    int x = 0, y= 50;
    frame_refresh_ai(x, y); /* Redraw a last time the frame */

    set_cursor(True); //이 함수로인해 터미널창 커서가 숨김에서 풀린다
    tcsetattr(0, TCSANOW, &back_attr); //TCSANOW는 즉시속성을 변경을 의미,

    printf("\n\n\t수고하셨습니다. 컴퓨터님의 레벨 %d, 점수는: %d입니다.\n\n", level2, score2);
    printf("\n\n\t\t\tpress enter to end the game!\n");
    while (1) {
        end = getchar();
        if (end == '\n')
            break;
    }
    set_cursor(True);
    tcsetattr(0, TCSANOW, &back_attr); //TCSANOW는 즉시속성을 변경을 의미, 터미널 세팅을 되돌리기
    system("clear"); //입력창이 다 밑으로 내려가서 이걸로하면 다시위로감

    finish2 = True;
    return;

}

void playAI()
{
    /*변수들*/
     level2 = 1;
     int n =1, i;
     int x = 0, y = 50;
     current2.last_move = False;
     lifes2 = 2;
     lines2 = 0;

     init_ai(); //게임 진행중에도 게임 사용법 보여
     frame_init_ai(x, y);
     frame_nextbox_init_ai(x, y);
      //여기까지 게임을 초기화하는 부분
    

     buf = 0;
	 //buf = current.x;
     while(running2)
     {
    	bestMoveHeu=-FLT_MAX;
      	int ranNum = nrand(1,300);

      	shape_set_ai();
      	if(score2<2000)       //레벨 5가 되면 블록이 안보임
	  	    {
            frame_refresh_ai(x, y);
            frame_preview_ai(x, y);
          }
      
      	 AI_shape_go_down(DEFAULT_COEFS);

      	if(score2> 2000)
	       printxy(0, FRAMEH_NB + 13, FRAMEW + 3, "***블록이 안보입니다***");

      	if(n >=1 && score2 >= 100)
        {
          	n--;
             block_down_ai();
        }

        if(ranNum == 108 )
          	n++;

		for (i = 2; i < FRAMEW - 1; i++) {
			if (frame2[1][i] != 0) {
				running2 = False;
			}
		}
     }	//이것이 게임루프의 주축이 되는 부분
     
     quit_ai();

}
