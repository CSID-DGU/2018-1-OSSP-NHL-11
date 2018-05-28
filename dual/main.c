/*
 * main.c
 *
 *  Created on: 2018. 5. 27.
 *      Author: kny
 */


#include "tetris.h"
#include "config.h"

int main(int argc, char **argv)
{
	running1 = True;
	running2 = True;
	finish1 = False;
	finish2 = False;

	while(1)
	{
		if(finish1 == False || finish2 == False){
			if(running1 == True){
				playUser();
			}
			else{
				//printf("d");
			}
			if(running2 == True){
				playAI();
			}
			else{
				//printf("d");
			}
		}
		else //finish1과 finish2의 값이 둘 중 하나라도 true면 게임 종료
			break;
	}
	return 0;
}
