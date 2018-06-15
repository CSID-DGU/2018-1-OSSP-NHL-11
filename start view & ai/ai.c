#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <unistd.h>
#include "tetris.h"

int n = 1;

void AI_shape_go_down(float *coefs) {
	int ranNum = nrand(1, 300);
    shape_unset();

    float moveHeu, bestMoveHeu = -FLT_MAX;
    int rotate, width, upper, count = 0;
    float temp;

    for (rotate = 0; rotate < 4; rotate++) {
    	usleep(10000);
        shape_set_position(rotate);
		for (width = 2; width < FRAMEW - 1; width += 2) {
			if (!check_possible_pos(buf, width)) //) && buf < FRAMEH - 2)
			{
//				/* 정사각형 */
//				if (current.num == 0)
//				{
//					// left side
//					for (upper = buf; upper > 1; upper--) {
//						if (frame[upper + 1][width] != 0)
//							count++;
//					}
//					if (count != 0) {
//						count = 0;
//						continue;
//					}
//					// right side
//					for (upper = buf; upper > 1; upper--) {
//						if (frame[upper + 1][width + 1] != 0)
//							count++;
//					}
//					if (count != 0) {
//						count = 0;
//						continue;
//					}
//				}
//
//				/* 일자형 막대 */
//				else if (current.num == 1)
//				{
//					if (rotate == 0 || rotate == 2) {	// garo(?)
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width + 3] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 1 || rotate == 3) {	// sero(?)
//						// left side & right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					}
//				}
//
//				/* 오른쪽 방향 ㄴ자 블록 */
//				else if (current.num == 2)
//				{
//					if (rotate == 0) {	// ____|
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 2][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width + 2] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 1) {	// ㄱ
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 2) {	// |----
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width + 2] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 3) {	// ㄴ
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 2][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					}
//				}
//
//				 /* 왼쪽 방향 ㄱ자 블록 */
//				else if (current.num == 3)
//				{
//					if (rotate == 0) {	// |____
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 2][width + 2] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 1) {	// ----|(opposite ㄴ)
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper+2][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 2) {	// ㄱ
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width + 2] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 3) {	// ----|(opposite ㄱ)
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					}
//				}
//
//				/* S자 블록 */
//				else if (current.num == 4)
//				{
//					if (rotate == 0 || rotate == 2) {	// __|--
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 2][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width + 2] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 1 || rotate == 3) {	// |__
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper+1][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					}
//				}
//
//				/* Z자 블록 */
//				else if (current.num == 5)
//				{
//					if (rotate == 0 || rotate == 2) {	// --|__
//					// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 2][width + 2] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 1 || rotate == 3) {	// |--
//					// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper+1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					}
//				}
//
//				/* T 블록 */
//				else if (current.num == 6)
//				{
//					if (rotate == 0) {	// _|_
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 2][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 2][width + 2] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 1) {	// |-
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper+1][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 2) {	// -|-
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper+1][width+2] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 3) {	// -|
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					}
//				}
//
//				/* + 블록 */
//				else if (current.num == 7)
//				{
//					// left side
//					for (upper = buf; upper > 1; upper--) {
//						if (frame[upper + 1][width] != 0)
//							count++;
//					}
//					if (count != 0) {
//						count = 0;
//						continue;
//					}
//					// right side
//					for (upper = buf; upper > 1; upper--) {
//						if (frame[upper + 1][width + 1] != 0)
//							count++;
//					}
//					if (count != 0) {
//						count = 0;
//						continue;
//					}
//				}
//
//				 /* . 블록 */
//				else if (current.num == 8) {
//					for (upper = buf; upper > 1; upper--) {
//						if (frame[upper + 1][width] != 0)
//							count++;
//					}
//					if (count != 0) {
//						count = 0;
//						continue;
//					}
//				}
//
//				/* small ㄱ자 블록 */
//				else if (current.num == 9) {
//					if (rotate == 0) {	// ㄱ
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 1) {	// opposite ㄴ
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 2][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper+1][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 2) {	// ㄴ
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper + 2][width + 1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					} else if (rotate == 3) {	// opposite ㄱ
//						// left side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper+1][width] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//						// right side
//						for (upper = buf; upper > 1; upper--) {
//							if (frame[upper+1][width+1] != 0)
//								count++;
//						}
//						if (count != 0) {
//							count = 0;
//							continue;
//						}
//					}
//				}
				/* 정사각형 */
					if (current.num == 0)
					{
						// left side
						for (upper = buf; upper > 1; upper--) {
							if (frame[upper + 1][width] != 0)
								count++;
						}
						if (count != 0) {
							count = 0;
							continue;
						}
						// right side
						for (upper = buf; upper > 1; upper--) {
							if (frame[upper + 1][width + 2] != 0)
								count++;
						}
						if (count != 0) {
							count = 0;
							continue;
						}
					}

					/* 일자형 막대 */
					else if (current.num == 1)
					{
						if (rotate == 0 || rotate == 2) {	// garo(?)
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width + 6] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 1 || rotate == 3) {	// sero(?)
							// left side & right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						}
					}

					/* 오른쪽 방향 ㄴ자 블록 */
					else if (current.num == 2)
					{
						if (rotate == 0) {	// ____|
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 2][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width + 4] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 1) {	// ㄱ
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 2) {	// |----
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width + 4] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 3) {	// ㄴ
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 2][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						}
					}

					 /* 왼쪽 방향 ㄱ자 블록 */
					else if (current.num == 3)
					{
						if (rotate == 0) {	// |____
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 2][width + 4] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 1) {	// ----|(opposite ㄴ)
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper+2][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 2) {	// ㄱ
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width + 4] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 3) {	// ----|(opposite ㄱ)
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						}
					}

					/* S자 블록 */
					else if (current.num == 4)
					{
						if (rotate == 0 || rotate == 2) {	// __|--
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 2][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width + 4] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 1 || rotate == 3) {	// |__
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper+1][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						}
					}

					/* Z자 블록 */
					else if (current.num == 5)
					{
						if (rotate == 0 || rotate == 2) {	// --|__
						// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 2][width + 4] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 1 || rotate == 3) {	// |--
						// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper+1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						}
					}

					/* T 블록 */
					else if (current.num == 6)
					{
						if (rotate == 0) {	// _|_
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 2][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 2][width + 4] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 1) {	// |-
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper+1][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 2) {	// -|-
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper+1][width+4] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 3) {	// -|
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						}
					}

					/* + 블록 */
					else if (current.num == 7)
					{
						// left side
						for (upper = buf; upper > 1; upper--) {
							if (frame[upper + 1][width] != 0)
								count++;
						}
						if (count != 0) {
							count = 0;
							continue;
						}
						// right side
						for (upper = buf; upper > 1; upper--) {
							if (frame[upper + 1][width + 2] != 0)
								count++;
						}
						if (count != 0) {
							count = 0;
							continue;
						}
					}

					 /* . 블록 */
					else if (current.num == 8) {
						for (upper = buf; upper > 1; upper--) {
							if (frame[upper + 1][width] != 0)
								count++;
						}
						if (count != 0) {
							count = 0;
							continue;
						}
					}

					/* small ㄱ자 블록 */
					else if (current.num == 9) {
						if (rotate == 0) {	// ㄱ
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 1) {	// opposite ㄴ
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 2][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper+1][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 2) {	// ㄴ
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper + 2][width + 2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						} else if (rotate == 3) {	// opposite ㄱ
							// left side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper+1][width] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
							// right side
							for (upper = buf; upper > 1; upper--) {
								if (frame[upper+1][width+2] != 0)
									count++;
							}
							if (count != 0) {
								count = 0;
								continue;
							}
						}
					}

				//printf("current.x : %d current.y : %d\n", current.x, current.y);
				temp = heuristic(coefs);
				if (bestMoveHeu < temp) {
					usleep(100000);
					//printf("**current.x : %d **current.y : %d\n", current.x, current.y);
					bestMoveHeu = temp;
					current.y = width;
					current.x = buf;
				}
			} else if (buf >= FRAMEH - 2) {
				usleep(100000);
				shape_new();
				bestMoveHeu = -FLT_MAX;
				buf = 0;
			}
		}
	}

    if (n >= 1 && score >= 50) {//100
      		n--;
      		block_down();
      	}

      	if (ranNum == 108)
      		n++;
    buf++;
    //return;
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

/* Returns the number of full lines */
int countCompleteLines() {
    int i, j;
    int counter = 0, rowCounter = 0;
    int gameHeight = maxHeight();

    for (i = FRAMEH - 1; i >= gameHeight; i--) {
        j = 0;
        counter = 0;
        while (frame[i][j] != 0 && j < FRAMEW) {
            j += 2;
            counter += 2;
        }
        if (counter == FRAMEW - 4)
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
