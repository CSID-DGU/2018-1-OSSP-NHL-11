#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tetris.h"
#define FRAMEH_NB 8
#define FRAMEW_NB 18

int frame[T_HEIGHT + 1][T_WIDTH + 1];
int frame_nextbox[FRAMEH_NB][FRAMEW_NB];

void displayGameBoard(Game* game) {
	short i, j;
	printf("□□□□□□□□□□□□□□\n");//##############\n");//□
	for(i=TETRI_SIZE; i<T_HEIGHT; i++) {
		printf("□");
		for(j=0; j<T_WIDTH; j++) {
			if(getBitboardValue(game->array[i], j) != 0)
				printf("□");
			else
				printf(" ");
		}
		printf("□");
		printf("\n");
	}
	printf("□□□□□□□□□□□□□□\n");
}


void frame_init(void)        //프레임의 색깔지정과 그리기
{
	int i;

	/* Frame border */
	for (i = 0; i < T_WIDTH + 1; ++i) {
		frame[0][i] = Border;         //윗테두리 색깔지정
		frame[T_HEIGHT][i] = Border;    //래테두리 색깔지정
	}
	for (i = 0; i < T_HEIGHT; ++i) {
		frame[i][0] = Border;           //왼쪽 테두리 색깔지정
		frame[i][1] = Border;           //왼쪽 테두리 색깔지정
		frame[i][T_WIDTH] = Border;      //오른쪽 테두리 색깔지정
		frame[i][T_WIDTH - 1] = Border;  //오른쪽 테두리 색깔지정
	}

	frame_refresh();     //테두리 그려줌

	return;
}

//void frame_nextbox_init(void)      //다음 나올 모양의 테두리 색깔 지정
//{
//	int i;
//
//	for (i = 0; i < FRAMEH_NB; ++i) {
//		frame_nextbox[i][0] = Border;
//		frame_nextbox[i][1] = Border;
//		frame_nextbox[i][FRAMEW_NB - 1] = Border;
//		frame_nextbox[i][FRAMEW_NB] = Border;
//
//	}
//	/*border는 색이름이고 nextbox의 테두리의 색깔을 입히는 함수이다.
//
//	 */
//	for (i = 0; i < FRAMEW_NB + 1; ++i)
//		frame_nextbox[0][i] = frame_nextbox[FRAMEH_NB][i] = Border;
//
//	frame_nextbox_refresh();    //다음나올 상자
//
//	return;
//}

void printxy(int color, int x, int y, char *str)
{
	set_color(color);	//색 지정
	printf("\e[%d;%dH%s", ++x, ++y, str);
	set_color(0);	//초기화

	return;
}

void set_color(int color)	//색을 지정
{
	int bg = 0, fg = 0;

	//bg : backgound, fg : foreground

	switch (color)	//각각의 색에 bg를 지정
	{
	default:
	case Black:
		bg = 0;
		break;
	case Blue:
		bg = 44;
		break;
	case Red:
		bg = 41;
		break;
	case Magenta:
		bg = 45;
		break;
	case White:
		bg = 47;
		break;
	case Green:
		bg = 42;
		break;
	case Cyan:
		bg = 46;
		break;
	case Yellow:
		bg = 43;
		break;
	case Test:
		bg = 41;
		break;
	case Test_2:
		bg = 41;
		break;
	case Test_3:
		bg = 42;
		break;
	case Border:
		bg = 47;
		break;
	case Score:
		fg = 37;
		bg = 49;
		break;
	}

	printf("\e[%d;%dm", fg, bg);

	return;
}

void frame_refresh(void)      //테트리스 테두리
{
	int i, j;

	for (i = 0; i < T_HEIGHT + 1; ++i) {
		for (j = 0; j < T_WIDTH + 1; ++j) {
			if (j % 2 == 1) {
				printxy(frame[i][j], i, j, " ");
			} else {
				if (i == 0 || i == T_HEIGHT || j == 0 || j == T_WIDTH - 1) {
					printxy(frame[i][j], i, j, " ");
				} else if (frame[i][j] != 0) {
					printxy(frame[i][j], i, j, "□");
				} else
					printxy(frame[i][j], i, j, " ");
			}
		}
	}
	return;
}

void frame_preview(void)
{
	int i, j;
	int temp;

	for (i = 0; i < T_HEIGHT + 1; ++i)//높이만큼
	{
		for (j = 0; j < T_WIDTH - 1; ++j)//너비만큼
		{
			if (j % 2 == 1)//블록 하나가 두 칸을 차지하기 때문에 홀수 칸은 다 빈칸으로 지정
			{
				printxy(frame[i][j], i, j, " ");
			}
			else //짝수 칸 중
			{
				if (i == 0 || i == T_HEIGHT || j == 0 || j == T_WIDTH - 1)//테두리 칸이라면 빈칸으로 지정
				{
					printxy(frame[i][j], i, j, " ");
				}
				else if (frame[i][j] != 0) //블럭이 있으면 블록의 밑쪽으로 ▽표시 나오도록
				{						  //: 모든 블록의 밑에 ▽가 나와버림! 내려오고 있는 블록의 아래에만 나와야하는데.
					for (int k = i; k < T_HEIGHT - 1; ++k)
					{
						if (frame[k + 1][j] == 0) //내려오고 있는 블록의 밑쪽이 비어있다면
							printxy(frame[k + 1][j], k + 1, j, "▽");//▽출력
					}
				}
			}
		}
	}
}
//
//void frame_nextbox_refresh(void)       //다음나올 상자와 모양
//{
//	int i, j;
//
//	/* Clean frame_nextbox[][] */       //테트리스 다음나올 모양상자 안쪽의 값 초기화 (색지정)
//	for (i = 1; i < FRAMEH_NB; ++i)
//		for (j = 2; j < FRAMEW_NB - 1; ++j)
//			frame_nextbox[i][j] = 0;
//
//	/* Set the shape in the frame */     //다음나올 모양 그려줌
//	for (i = 0; i < 5; ++i)
//		for (j = 0; j < EXP_FACT; ++j)
//			frame_nextbox       //맨앞 숫자는 위치지정, current.next는 0부터 6까지 난수로 모양 지정
//			[2 + shapes[current.next][sattr[current.next][2]][i][0]
//					+ sattr[current.next][0]][4
//					+ shapes[current.next][sattr[current.next][2]][i][1]
//							* EXP_FACT + j + sattr[current.next][1]] =
//					current.next + 1;  //다른변수들은 모양 지정
//
//		/* Draw the frame */
//	for (i = 0; i < FRAMEH_NB + 1; ++i)              //테트리스 다음나올 모양 테두리 그려줌
//		for (j = 0; j < FRAMEW_NB + 1; ++j) {
//			if (j % 2 == 1) {
//				printxy(frame_nextbox[i][j], i, j + FRAMEW + 3, " ");
//			} else {
//				if (i == 0 || i == FRAMEH_NB || j == 0 || j == FRAMEW_NB) {
//					printxy(frame_nextbox[i][j], i, j + FRAMEW + 3, " ");
//				} else if (frame_nextbox[i][j] != 0) {
//					printxy(frame_nextbox[i][j], i, j + FRAMEW + 3, "□");
//				} else
//					printxy(frame_nextbox[i][j], i, j + FRAMEW + 3, " ");
//			}
//		}
//
//	return;
//}
