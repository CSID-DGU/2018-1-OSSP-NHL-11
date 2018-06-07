#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "tetris.h"

void AI_shape_go_down(float *coefs) {

	shape_unset();
	float moveHeu, bestMoveHeu = -FLT_MAX;
	int rotate, width, upper, count = 0;
	float temp;
	for (rotate = 0; rotate < 4; rotate++) {
		shape_set_position(rotate);
		for (width = 2; width < FRAMEW - 1; width += 2) {
			if (!check_possible_pos(buf, width)) //) && buf < FRAMEH - 2)
					{
				for (upper = buf; upper > 1; upper--) {
					if (frame[upper][width] != 0) {
						count++;
					}
				}
				if (count != 0) {
					count = 0;
					continue;
				}
				temp = heuristic(coefs);
				if (bestMoveHeu < temp) {
					sleep(1);
					bestMoveHeu = temp;
					current.y = width;
					current.x = buf;
					//current.pos = rotate;
					// current.pos;
				}
			} else if (buf >= FRAMEH - 2) {
				shape_new();
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
	heuristicValue += holes * (float) countHoles();
	heuristicValue += height * (float) computeTotalHeight();
	heuristicValue += rows * (float) countCompleteLines();
	heuristicValue += hollowness * (float) computeHollowness();
	return heuristicValue;
}

/* Returns the number of full lines */
int countCompleteLines() {
	int i, j;
	int rowCounter = 0;
	int gameHeight = maxHeight();

	for (i = FRAMEH - 1; i >= gameHeight; i--) {
		j = 2;
		while (frame[i][j] != 0 && j < FRAMEW) {
			j += 2;
		}
		if (j == FRAMEW - 1)
			rowCounter++;
	}
	return rowCounter;
}

int maxHeight() {
	int i, j;
	for (i = 1; i < FRAMEH - 1; i++)
		for (j = 2; j < FRAMEW - 2; j += 2)
			if (frame[i][j] != 0) {
				return i;
			}
	return 0;
}

int countHoles() {
    int i, j, k, counter;
    int totalCounter = 0;
    for (i = 2; i < FRAMEH; i++) {
        for (j = 2; j < FRAMEW - 1; j += 2) {
            if (frame[i][j] == 0 && frame[i - 1][j] != 0) {
                counter = 0;
                k = i;
                while (frame[k][j] == 0 && k < FRAMEH) {
                    counter++;
                    k++;
                }
                k--;
                if (frame[k + 1][j] != 0)
                    totalCounter += counter;
            }
        }
    }
    return totalCounter;
}

int computeTotalHeight() {
	int i, j, height = 0;

	for (j = 2; j < FRAMEW - 2; j += 2) {
		for (i = 1; i < FRAMEH; i++) {
			if (frame[i][j] != 0) {
				height += FRAMEH - i;
				break;
			}
		}
	}
	return height;
}

/* Returns the summation of heights' differences between columns */
int computeHollowness() {
	int i;
	int summation = 0;
	int maxHeight[FRAMEW] = { 0, };
	for (i = 0; i < FRAMEW; i += 2) {
		if (i == 0 || i >= FRAMEW - 2)
			continue;
		maxHeight[i + 1] = maxHeight[i] = maxColumnHeight(i);
	}

	for (i = 2; i < FRAMEW - 2; i += 2) {
		summation += abs(maxHeight[i] - maxHeight[i + 2]);
	}

	return summation;
}

/* Returns the maximum height of a given column */
int maxColumnHeight(int columnNb) {
	if (columnNb < 2 || columnNb >= FRAMEW - 2)
		return 0;
	int i;
	for (i = 1; i < FRAMEH; i++) {
		if (frame[i][columnNb] != 0)
			return (FRAMEH - i);
	}
	return 0;
}
