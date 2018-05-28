/*
 * main.c
 *
 *  Created on: 2018. 5. 27.
 *      Author: kny
 */


#include "tetris.h"
#include "config.h"
/*#include <termio.h>

Bool kbhit()
{
	int ch = -1;
	struct termios old;
	struct termios new;

	tcgetattr(0, &old);

	new = old;
	new.c_lflag &= ~(ICANON|ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;

	tcsetattr(0, TCSAFLUSH, &new);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &old);

	if(ch == -1) return 0;
	else return 1;
}*/
int main(int argc, char **argv)
{
	char myname[10];
	first(myname);

    /*변수들*/
    level1 = 1;
    current1.last_move = False;
    lifes1 = 2;
    lines1 = 0;

    init_user(); //게임 진행중에도 게임 사용법 보여
    frame_init_user();
    frame_nextbox_init_user();

    /*변수들*/
     level2 = 1;
     current2.last_move = False;
     lifes2 = 2;
     lines2 = 0;

     init_ai(); //게임 진행중에도 게임 사용법 보여
     frame_init_ai(0, 50);
     frame_nextbox_init_ai(0, 50);
      //여기까지 게임을 초기화하는 부분

	while(1)
	{
		if(finish1 == False || finish2 == False){
/*				if(running1 == True){
					playUser();
				}
				else{
					 quit_user(myname);
				}

				if(running2 == True){
					playAI();
				}
				else{
					quit_ai();
				}*/
			if (running1 == True && running2 == True) {
				playUser();
				playAI();
			}
			if (running1 == False) {
				quit_user(myname);
			}

			if (running2 == False) {
				quit_ai();
			}
		}
		else //finish1과 finish2의 값이 둘 중 하나라도 true면 게임 종료
			break;
	}
	return 0;
}
