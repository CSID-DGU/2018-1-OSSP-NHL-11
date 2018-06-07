/*
 * frame.c
 *
 *  Created on: 2018. 5. 15.
 *      Author: kny
 */

#include "tetris.h"

/* Shape attribute for draw it in the next box (center etc..)
 * [0]: +x
 * [1]: +y
 * [2]: What shape position choose for a perfect position in the box
 */
const int sattr[10][3] = { { 1, 2 }, { 1, 2 }, { 0, 2, 1 }, { 0, 2 }, { 0, 2 },
		{ 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2, 0 } }; // Nextbox에서 출력되는 위치 고정

void frame_init(int x, int y)        //프레임의 색깔지정과 그리기
{
	int i;

	/* Frame border */
	for (i = 0; i < FRAMEW + 1; ++i) {
		frame[0][i] = Border;         //윗테두리 색깔지정
		frame[FRAMEH][i] = Border;    //래테두리 색깔지정
	}
	for (i = 0; i < FRAMEH; ++i) {
		frame[i][0] = Border;           //왼쪽 테두리 색깔지정
		frame[i][1] = Border;           //왼쪽 테두리 색깔지정
		frame[i][FRAMEW] = Border;      //오른쪽 테두리 색깔지정
		frame[i][FRAMEW - 1] = Border;  //오른쪽 테두리 색깔지정
	}

	frame_refresh(x,y);     //테두리 그려줌

	return;
}

void frame_nextbox_init(int x, int y)      //다음 나올 모양의 테두리 색깔 지정
{
	int i;

	for (i = 0; i < FRAMEH_NB; ++i) {
		frame_nextbox[i][0] = Border;
		frame_nextbox[i][1] = Border;
		frame_nextbox[i][FRAMEW_NB - 1] = Border;
		frame_nextbox[i][FRAMEW_NB] = Border;

	}
	/*border는 색이름이고 nextbox의 테두리의 색깔을 입히는 함수이다.

	 */
	for (i = 0; i < FRAMEW_NB + 1; ++i)
		frame_nextbox[0][i] = frame_nextbox[FRAMEH_NB][i] = Border;

	frame_nextbox_refresh(x,y);    //다음나올 상자

	return;
}

void frame_refresh(int x, int y)      //테트리스 테두리
{
	int i, j, k;

	for (i = 0; i < FRAMEH + 1; ++i) {
		for (j = 0; j < FRAMEW + 1; ++j) {
			if (j % 2 == 1) {
				printxy(frame[i][j], i+x, j+y, " ");
			} else {
				if (i == 0 || i == FRAMEH || j == 0 || j == FRAMEW - 1) {
					printxy(frame[i][j], i+x, j+y, " ");
				} else if (frame[i][j] != 0) {
					printxy(frame[i][j], i+x, j+y, "□");
				} else
					printxy(frame[i][j], i+x, j+y, " ");
			}
		}
	}
	/*
	 for(i = 0; i < FRAMEH + 1; ++i)
	 {
	 for(j = 0; j < FRAMEW + 1; ++j)
	 {
	 if(frame[i][j] != 0)
	 {
	 for(k = 0; k < FRAMEH + 1; ++k)
	 {
	 printxy(frame[k][j], k, j, "□");
	 }
	 }
	 }
	 }
	 */
	return;

}

void frame_preview(int x, int y) {
	int i, j;
	int temp;

	for (i = 0; i < FRAMEH + 1; ++i) {
		for (j = 0; j < FRAMEW - 1; ++j) {
			if (j % 2 == 1) {
				printxy(frame[i][j], i+x, j+y, " ");
			}

			else {
				if (i == 0 || i == FRAMEH || j == 0 || j == FRAMEW - 1) {
					printxy(frame[i][j], i+x, j+y, " ");
				} else if (frame[i][j] != 0) //위에 블럭이 있을때
					{
					for (int k = i; k < FRAMEH - 1; ++k) {
						if (frame[k + 1][j] == 0) //블록부분의 영역이 바뀌는걸 막아줌
							printxy(frame[k + 1][j], k+1+x, j+y, "▽");
					}
				}
			}

		}
	}

	return;

}

void frame_nextbox_refresh(int x, int y)       //다음나올 상자와 모양
{
	int i, j;

	/* Clean frame_nextbox[][] */       //테트리스 다음나올 모양상자 안쪽의 값 초기화 (색지정)
	for (i = 1; i < FRAMEH_NB; ++i)
		for (j = 2; j < FRAMEW_NB - 1; ++j)
			frame_nextbox[i][j] = 0;

	/* Set the shape in the frame */     //다음나올 모양 그려줌
	for (i = 0; i < 5; ++i)
		for (j = 0; j < EXP_FACT; ++j)
			frame_nextbox       //맨앞 숫자는 위치지정, current.next는 0부터 6까지 난수로 모양 지정
			[2 + shapes[current.next][sattr[current.next][2]][i][0]
					+ sattr[current.next][0]][4
					+ shapes[current.next][sattr[current.next][2]][i][1]
							* EXP_FACT + j + sattr[current.next][1]] =
					current.next + 1;  //다른변수들은 모양 지정

		/* Draw the frame */
	for (i = 0; i < FRAMEH_NB + 1; ++i)              //테트리스 다음나올 모양 테두리 그려줌
		for (j = 0; j < FRAMEW_NB + 1; ++j) {
			if (j % 2 == 1) {
				printxy(frame_nextbox[i][j], i+x, j + FRAMEW + 3+y, " ");
			} else {
				if (i == 0 || i == FRAMEH_NB || j == 0 || j == FRAMEW_NB) {
					printxy(frame_nextbox[i][j], i+x, j + FRAMEW + 3+y, " ");
				} else if (frame_nextbox[i][j] != 0) {
					printxy(frame_nextbox[i][j], i+x, j + FRAMEW + 3+y, "□");
				} else
					printxy(frame_nextbox[i][j], i+x, j + FRAMEW + 3+y, " ");
			}
		}

	return;
}

