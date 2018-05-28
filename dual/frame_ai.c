/*
 *      frame.c
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


/* Shape attribute for draw it in the next box (center etc..)
 * [0]: +x
 * [1]: +y
 * [2]: What shape position choose for a perfect position in the box
 */
const int sattr2[10][3] = {{1,2}, {1,2}, {0,2,1}, {0,2}, {0,2}, {1,2}, {1,2}, {1,2} ,{1,2}, {1,2,0}}; // Nextbox에서 출력되는 위치 고정

void frame_init_ai(int x, int y)        //프레임의 색깔지정과 그리기
{
     int i;

     /* Frame border */
     for(i = 0; i < FRAMEW + 1; ++i)
     {
          frame2[0][i] = Border;         //윗테두리 색깔지정
          frame2[FRAMEH][i] = Border;    //래테두리 색깔지정
     }
     for(i = 0; i < FRAMEH; ++i)
     {
          frame2[i][0] = Border;           //왼쪽 테두리 색깔지정
          frame2[i][1] = Border;           //왼쪽 테두리 색깔지정
          frame2[i][FRAMEW] = Border;      //오른쪽 테두리 색깔지정
          frame2[i][FRAMEW - 1] = Border;  //오른쪽 테두리 색깔지정
     }

     frame_refresh_ai(x, y);     //테두리 그려줌

     return;
}

void frame_nextbox_init_ai(int x, int y)      //다음 나올 모양의 테두리 색깔 지정
{
     int i;

     for(i = 0; i < FRAMEH_NB; ++i)  
     {
          frame_nextbox2[i][0] = Border;
          frame_nextbox2[i][1] = Border;
          frame_nextbox2[i][FRAMEW_NB - 1] = Border;
          frame_nextbox2[i][FRAMEW_NB] = Border;

     }
     /*border는 색이름이고 nextbox의 테두리의 색깔을 입히는 함수이다. 

     */
     for(i = 0; i < FRAMEW_NB + 1; ++i)
          frame_nextbox2[0][i] = frame_nextbox2[FRAMEH_NB][i] = Border;

     frame_nextbox_refresh_ai(x, y);    //다음나올 상자

     return;
}

void frame_refresh_ai(int x, int y)      //테트리스 테두리
{
     int i, j, k;


     for(i = 0; i < FRAMEH + 1; ++i)
     {
          for(j = 0; j < FRAMEW + 1; ++j)
	  {
		if(j%2 == 1)
		{	
                    printxy(frame2[i][j], i+x, j+y, " ");
		}
		else
		{
		    if(i == 0 || i == FRAMEH || j == 0 || j == FRAMEW - 1)
		    {
   		        printxy(frame2[i][j], i+x, j+y, " ");
		    }
		    else if(frame2[i][j] != 0)
		    {
			printxy(frame2[i][j], i+x, j+y, "□");
	 	    }
		    else
			printxy(frame2[i][j], i+x, j+y, " ");
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

void frame_preview_ai(int x, int y)
{
     int i, j;
     int temp;

     for(i = 0; i < FRAMEH + 1; ++i)
     {
          for(j = 0; j < FRAMEW - 1; ++j)
	  {
		    if(j%2 == 1)
		    {	
                  	printxy(frame2[i][j], i+x, j+y, " ");
		    }

		    else 
		    {
		    	if(i == 0 || i == FRAMEH || j == 0 || j == FRAMEW - 1)
		    	{
   		     	   printxy(frame2[i][j], i+x, j+y, " ");
		   	    }
			    else if(frame2[i][j] != 0) //위에 블럭이 있을때
			    {
				    for(int k = i; k < FRAMEH - 1; ++k) 
			    	{
                        if(frame2[k+1][j] == 0) //블록부분의 영역이 바뀌는걸 막아줌
                            printxy(frame2[k + 1][j], k + 1+x, j+y, "▽");
				    }	
			    }
	 	    }

          }
     }



     return;

}

void
frame_nextbox_refresh_ai(int x, int y)       //다음나올 상자와 모양
{
     int i, j;

     /* Clean frame_nextbox[][] */       //테트리스 다음나올 모양상자 안쪽의 값 초기화 (색지정) 
     for(i = 1; i < FRAMEH_NB; ++i)
          for(j = 2; j < FRAMEW_NB - 1; ++j)
               frame_nextbox2[i][j] = 0;

     /* Set the shape in the frame */     //다음나올 모양 그려줌 
     for(i = 0; i < 5; ++i)
          for(j = 0; j < EXP_FACT; ++j)
               frame_nextbox2       //맨앞 숫자는 위치지정, current.next는 0부터 6까지 난수로 모양 지정
                    [2 + shapes2[current2.next][sattr2[current2.next][2]][i][0] + sattr2[current2.next][0]]
                    [4 + shapes2[current2.next][sattr2[current2.next][2]][i][1] * EXP_FACT + j + sattr2[current2.next][1]]
                    = current2.next + 1;  //다른변수들은 모양 지정

     /* Draw the frame */
     for(i = 0; i < FRAMEH_NB + 1; ++i)              //테트리스 다음나올 모양 테두리 그려줌 
          for(j = 0; j < FRAMEW_NB + 1; ++j)
          {
		if(j%2 == 1)
		{	
                    printxy(frame_nextbox2[i][j], i+x, j + FRAMEW + 3 +y , " ");
		}
		else 
		{
		    if(i == 0 || i == FRAMEH_NB || j == 0 || j == FRAMEW_NB)
		    {
		     	printxy(frame_nextbox2[i][j], i+x, j + FRAMEW + 3+y, " ");
		    }
		    else if(frame_nextbox2[i][j] != 0)
		    {
		    	printxy(frame_nextbox2[i][j], i+x, j + FRAMEW + 3+y, "□");
	 	    }
		    else
			printxy(frame_nextbox2[i][j], i+x, j + FRAMEW + 3+y, " ");
		}
	  }


     return;
}

