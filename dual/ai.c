
#include <stdlib.h>
#include <stdio.h>
#include "tetris.h"

void AI_shape_go_down(float *coefs) {
    shape_unset();
    float moveHeu, bestMoveHeu = -FLT_MAX;
    int rotate, width, upper, count = 0;
    int x = 0, y = 50;
    float temp;
    for (rotate = 0; rotate < 4; rotate++)
    {
        shape_set_position(rotate);
        for (width = 2; width < FRAMEW - 1; width += 2)
        {
            if (!check_possible_pos(buf, width))//) && buf < FRAMEH - 2)
             {
              for(upper = buf; upper > 1; upper--)
                {
                    if(frame[upper][width] != 0)
                    {
                        count++;
                    }
                }
                if(count != 0)
                {
                    count = 0;
                    continue;
                }
                temp = heuristic(coefs);
                if (bestMoveHeu < temp)
                {
                    sleep(1);
                    bestMoveHeu = temp;
                    current.y = width;
                    current.x = buf;
                    //current.pos = rotate;
                    // current.pos;
                }
            }
            else if (buf >= FRAMEH - 2)
             {
                   shape_new(x, y);
                   bestMoveHeu = -FLT_MAX;
                   buf = 0;
             }
        }
    }
    buf++;
}

float heuristic(float* coefs) {
    float rows = coefs[0];
    float height = coefs[1];
    float holes = coefs[2];
    float hollowness = coefs[3];
    float heuristicValue = 0.0;
    heuristicValue += holes * (float)countHoles();
    heuristicValue += height * (float)computeTotalHeight();
    heuristicValue += rows * (float)countCompleteLines();
    heuristicValue += hollowness * (float)computeHollowness();
    return heuristicValue;
}

int countHoles()
{
    int totalcount=0, count=0, flag=0;
    int i, j, k;
    for(i=1;i<FRAMEH;i++)
    {
        for(j=2;j<FRAMEW-1;j+=2)
        {
            if(frame[i][j]!=0)
                flag=1;
        }
        if (flag == 1) {
            for (j = 2; j < FRAMEW - 1; j += 2) {
                if (frame[i][j] == 0) {
                    count = 0;
                    k = i;
                    while (frame[k][j] == 0 && k < FRAMEH) {
                        count++;
                        k++;
                    }
                    k--;
                    if (frame[k][j] != 0)
                        totalcount += count;
                }
            }
            flag = 0;
        }

    }
    return totalcount;
}

int computeTotalHeight()
{
	int height = 0;
    int i, j;
    for (i = 1; i < FRAMEH; i++) {
        for (j = 2; j < FRAMEW - 1; j += 2) {
            if (frame[i][j] != 0)
            {
                height += FRAMEH-i;
            }
        }
    }
    return height;
}

/* Returns the number of full lines */
int countCompleteLines()
{
    int i, j;
    int counter = 0, rowCounter = 0;
    int gameHeight = maxHeight();

    for(i=FRAMEH-1; i>=gameHeight; i--) {
        j=0;
        counter = 0;
        while(frame[i][j] !=0 && j < FRAMEW) {
            j+=2;
            counter++;
        }
        if(counter == FRAMEW)
            rowCounter++;
    }
    return rowCounter;
}

int maxHeight() {
    int i, j;
    for(i=1; i<FRAMEH-1; i++)
        for(j=2; j<FRAMEW-2; j+=2)
            if(frame[i][j] != 0) {
                return i;
            }
    return 0;
}

/* Returns the summation of heights' differences between columns */
int computeHollowness() {
    int i;
    int summation = 0;
    int maxHeight[FRAMEW-4];

    for(i=0; i<FRAMEW-4; i+=2) {
        maxHeight[i] = maxColumnHeight(i);
        maxHeight[i+1] = maxHeight[i];
    }

    for(i=0; i<FRAMEW-4; i+=2)
        summation += abs(maxHeight[i] - maxHeight[i+2]);

    return summation;
}

/* Returns the maximum height of a given column */
int maxColumnHeight(int columnNb) {
    if(columnNb < 0 || columnNb >= FRAMEW-4)
        return 1;
    int i;
    for(i=1; i<FRAMEH-1; i++) {
        if(frame[i][columnNb] == 1)
            return (FRAMEH - i);
    }
    return 0;
}
