/*
 * process.c
 *
 *  Created on: 2018. 5. 15.
 *      Author: kny
 */

#include "tetris.h"
#include "config.h"
#include <float.h>

float DEFAULT_COEFS[COEF_NB] = { 0.728118, -0.194489, -0.913055, -0.130114  };//{ 0.244451, -0.190498, -0.491333, -0.001709 };
const char *Logo[] = {

		" /######## /######## /######## /#######  /######  /###### ",
		"|__  ##__/| ##_____/|__  ##__/| ##__  ##|_  ##_/ /##__  ##",
		"   | ##   | ##         | ##   | ##  \\ ##  | ##  | ##  \\__/",
		"   | ##   | #####      | ##   | #######/  | ##  |  ###### ",
		"   | ##   | ##__/      | ##   | ##__  ##  | ##   \\____  ##",
		"   | ##   | ##         | ##   | ##  \\ ##  | ##   /##  \\ ##",
		"   | ##   | ########   | ##   | ##  | ## /######|  ######/",
		"   |__/   |________/   |__/   |__/  |__/|______/ \\______/ "

	};

/* Functions */
/*char* first(char * name) {

	int i, j;
	//char start;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 60; j++) {
				printf("%c", Logo[i][j]);
		}
		printf("\n");
	}

	printf("\n\n\t당신의 이름은? ");
	scanf("%s", name);
	/*	printf("\n\n\t\t\tpress enter to enter game!");	 //tab세번이 적절
	 while (1) {
	 start = getchar();
	 if (start == '\n')
	 break;
	 }*/
	//return name;
//}*/


void init1(void) {

	struct sigaction siga1;
	struct termios term;

	/* Clean term */
	//clear_term();
	set_cursor(False);
	/* Init terminal (for non blocking & noecho getchar();
	 이것을 위로 옮긴 이유는 처음부터 껌벅커서를 지우기 위해*/
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &back_attr);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	/*스타트함수를 init에 통합했다*/
	set_cursor(False); //커서없애줌

	/* Make rand() really random :) */
	srand(getpid());

	/* Init variables */
	score = 0;

	running = True; //true일 경우에 게임의 축이 되는 루프가 계속 돌아가고 false일 경우 루프가 break되고 quit함수가 호출되어 종료된다

	current.y = (FRAMEW / 2) - 1;
	current.num = nrand(0, 7); //7가지블록랜덤
	current.next = nrand(0, 7); //다음 블록의 종류를 정함

	/* Score(오른쪽에 표시되는 안내사항을 보여주는 */
	printxy(0, FRAMEH_NB + 2, FRAMEW + 3, "Level : ");
	printxy(0, FRAMEH_NB + 3, FRAMEW + 3, "Score : ");
	//printxy(0, FRAMEH_NB + 4, FRAMEW + 3, "Lines : ");
	DRAW_SCORE()
	;

	printxy(0, FRAMEH_NB + 1, FRAMEW + 80, "Left  : ←");
	printxy(0, FRAMEH_NB + 2, FRAMEW + 80, "Right : →");
	printxy(0, FRAMEH_NB + 3, FRAMEW + 80, "Change: ↑");
	printxy(0, FRAMEH_NB + 4, FRAMEW + 80, "Down  : ↓");
	printxy(0, FRAMEH_NB + 5, FRAMEW + 80, "Drop  : Space Bar");
	printxy(0, FRAMEH_NB + 6, FRAMEW + 80, "Pause : p");
	printxy(0, FRAMEH_NB + 7, FRAMEW + 80, "Quit  : q");

	/* Init signal */

	sigemptyset(&siga1.sa_mask);
	siga1.sa_flags = 0;
	siga1.sa_handler = sig_handler;
	sigaction(SIGALRM, &siga1, NULL);
	sigaction(SIGTERM, &siga1, NULL);
	sigaction(SIGINT, &siga1, NULL);
	sigaction(SIGSEGV, &siga1, NULL);

	/* Init timer */
	tv.it_value.tv_usec = TIMING;
	sig_handler(SIGALRM);

	return;
}
void init2() {
	struct sigaction siga;
	struct termios term;

	/* Clean term */
	//clear_term();
	set_cursor(False);
	/* Init terminal (for non blocking & noecho getchar();
	 이것을 위로 옮긴 이유는 처음부터 껌벅커서를 지우기 위해*/
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &back_attr);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
	/*스타트함수를 init에 통합했다*/
	set_cursor(False); //커서없애줌

	/* Make rand() really random :) */
	srand(getpid());

	/* Init variables */
	score = 0;

	running = True; //true일 경우에 게임의 축이 되는 루프가 계속 돌아가고 false일 경우 루프가 break되고 quit함수가 호출되어 종료된다

	current.y = (FRAMEW / 2) - 1;
	current.num = nrand(0, 7); //7가지블록랜덤
	current.next = nrand(0, 7); //다음 블록의 종류를 정함

	/* Score(오른쪽에 표시되는 안내사항을 보여주는 */
	printxy(0, FRAMEH_NB + 2, FRAMEW + 53, "Level : ");
	printxy(0, FRAMEH_NB + 3, FRAMEW + 53, "Score : ");
	//printxy(0, FRAMEH_NB + 4, FRAMEW + 53, "Lines : ");

	DRAW_SCORE2()
	;

	/* Init signal */
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = 0;
	siga.sa_handler = sig_handler;
	sigaction(SIGALRM, &siga, NULL);
	sigaction(SIGTERM, &siga, NULL);
	sigaction(SIGINT, &siga, NULL);
	sigaction(SIGSEGV, &siga, NULL);

	/* Init timer */
	tv.it_value.tv_usec = TIMING;
	sig_handler(SIGALRM);

	return;

}
void get_key_event(void) {

	int c = getchar();

	if (c > 0)
		--current.x;
	/*main함수중에 전체 루프중에 필수적으로 거치는 함수이자 입력받은 값에따라 게임 진행이 된다.
	 여기서 key_pause와 key_quit는 게임을 계속 진행하는 대에 영향을 준다*/
	switch (c) {
	case KEY_MOVE_LEFT:
		shape_move(-EXP_FACT);
		break;
	case KEY_MOVE_RIGHT:
		shape_move(EXP_FACT);
		break;
	case KEY_MOVE_DOWN:
		++current.x;
		++score;
		DRAW_SCORE()
		;
		break;
	case KEY_CHANGE_POSITION_NEXT:
		shape_set_position(N_POS);
		break;
	case KEY_DROP_SHAPE:
		shape_drop();
		break;
	case KEY_PAUSE:
		while (getchar() != KEY_PAUSE)
			;
		break;
	case KEY_QUIT:
		running = False;
		break;
	case 'Q':
		running = False;
		break; //대문자 Q를 사용할 때 종료
		/*	case 'r':
		 if (lifes != 0)
		 revive();
		 break;*/
		//case 't':                      sleep(5);                         break; //5초 정지
		//시간 멈추는 능력
	}

	return;
}

void arrange_score(int l, int play) {
	/* 클리어한 라인에따라 점수부여. 여기서 의문점이 5줄이상일때 에러가 발생하는지
	 테트리스는 5줄이상 못깹니다.  */
	switch (l) {
	case 1:
		score += 40;
		break; /* One line */
	case 2:
		score += 80;
		break; /* Two lines */
	case 3:
		score += 100;
		break; /* Three lines */
	case 4:
		score += 200;
		break; /* Four lines */
	}

	if (score >= 100)  //레벨 추가
		level = 2;
	if (score >= 500)
		level = 3;
	if (score >= 1000)
		level = 4;
	if (score >= 2000)
		level = 5;
	//lines += l;

	if (play == 0) {
		DRAW_SCORE()
		;
	} else {
		DRAW_SCORE2()
		;
	}

	return;
}

void check_plain_line(int x, int y) {
	int i, j, k, f, c = 0, nl = 0;

	for (i = 1; i < FRAMEH; ++i) {
		for (j = 1; j < FRAMEW; ++j)
			if (frame[i][j] == 0)
				++c;
		if (!c) {
			usleep(1000000);
			++nl;
			//sound("pop.wav",400);
			for (k = i - 1; k > 1; --k)
				for (f = 1; f < FRAMEW; ++f)
					frame[k + 1][f] = frame[k][f];
		}
		c = 0;
	}
	arrange_score(nl, y);
	frame_refresh(x, y);

	return;
}

int check_possible_pos(int x, int y) {
	int i, j, c = 0;

	for (i = 0; i < 5; ++i)
		for (j = 0; j < EXP_FACT; ++j)
			if (frame[x + shapes[current.num][current.pos][i][0]][y
					+ shapes[current.num][current.pos][i][1] * EXP_FACT + j]
					!= 0)
				++c;

	return c;
}

void quit(int x, int y, int *share) {	

	char end;
	frame_refresh(x, y); /* Redraw a last time the frame */
	share[1] = score; //user_score

	
	set_cursor(True);
	tcsetattr(0, TCSANOW, &back_attr); //TCSANOW는 즉시속성을 변경을 의미, 터미널 세팅을 되돌리기
	
	return;
}
void ai_quit(int x, int y, int *share) {
	char end;
	frame_refresh(x, y); /* Redraw a last time the frame */
	share[2] = score;

	set_cursor(True); //이 함수로인해 터미널창 커서가 숨김에서 풀린다
	tcsetattr(0, TCSANOW, &back_attr); //TCSANOW는 즉시속성을 변경을 의미,

	return;
}

void play(int x, int y, int *share) {
	frame_init(x, y);
	frame_nextbox_init(x, y);

	level = 1;
	int n = 1;
	current.last_move = False;
	//lines = 0;

	//shape_unset();
	//여기까지 게임을 초기화하는 부분
	while (running) {

		int ranNum = nrand(1, 300);
		get_key_event();
		shape_set();

		//레벨 5가 되면 블록이 안보임
		if (score < 2000) {
			frame_refresh(x, y);
			frame_preview(x, y);
		}

		shape_go_down(x, y);

		if (score > 2000)
			printxy(0, FRAMEH_NB + 13 + x, FRAMEW + 3 + y, "***블록이 안보입니다***");

		if (n >= 1 && score >= 100) {
			n--;
			block_down();
			//sound("nope.wav", 400);
		}

		if (ranNum == 108)
			n++;

		for (int i = 2; i < FRAMEW - 1; i++) {
			if (frame[1][i] != 0)
				running = False;
		}
		if (share[0] == 5) //ai가 먼저 끝나면 강제 게임 종료
			break;
		//shape_unset();

	}
	//이것이 게임루프의 주축이 되는 부분
}
void playAI(int x, int y, int *share) {
	frame_init(x, y);
	frame_nextbox_init(x, y);

	level = 1;
  	int i;
	int n = 1;
	current.last_move = False;
	//lines = 0;
	buf = 0;
	flag2 = 0;
	running = True;
	while (running) {
		//bestMoveHeu = -FLT_MAX;
		int ranNum = nrand(1, 300);

		shape_set();
		if (score < 2000)       //레벨 5가 되면 블록이 안보임
				{
			frame_refresh(x, y);
			frame_preview(x, y);
		}

		AI_shape_go_down(DEFAULT_COEFS);

		if (buf >= FRAMEH - 2) {
			usleep(100000);
			flag2 = 1;	// when one block checks all!
			shape_new(x, y);
			bestMoveHeu = -FLT_MAX;
			buf = 0;
		}

		if (score > 2000)
			printxy(0, FRAMEH_NB + 13, FRAMEW + 3, "***블록이 안보입니다***");

		if (n >= 1 && score >= 100 && flag2 == 1) {
			n--;
			block_down();
			flag2 = 0;

		}

		if (ranNum == 108)
			n++;
		flag2=0;

		for (int i = 2; i < FRAMEW - 1; i++) {
			if (frame[4][i] != 0) {

				running = False;
			}
		}
		if (share[0] == 8) //user가 먼저 끝나면 강제 게임 종료
			break;
	}	//이것이 게임루프의 주축이 되는 부분
}
int main(int argc, char **argv) {

	char name[10];
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 59; j++) {
				printf("%c", Logo[i][j]);
		}
		printf("\n");
	}

	printf("\n\n\t당신의 이름은? ");
	scanf("%s", name);
	clear_term();

	void *shared_memory = (void *) 0;
	int shmid;
	int status;
	int *share = (int *) malloc(sizeof(int) * 3);

	//공유 메모리 공간을 만든다.
	shmid = shmget((key_t) 1234, sizeof(int), 0666 | IPC_CREAT);
	if (shmid == -1) {
		perror("shmget failed: ");
		exit(0);
	}

	//공유 메모리를 사용하기 위해 프로세스 메모리에 붙인다.
	shared_memory = shmat(shmid, (void *) 0, 0);
	if (shared_memory == (void *) -1) {
		perror("shmat failed: ");
		exit(0);
	}
	share = (int *) shared_memory;
	share[0] = 0; //종료를 체크하는 flag 변수처럼 사용

	pid_t game = fork();

	int ai_score, user_score;

	switch (game) {
	case -1: {
		printf("자식 프로세스 생성 실패\n");
		return -1;
	}
	case 0: { //자식 프로세스 = user
		init1();
		play(0, 0, share); //이 함수 내부에 while문과 종료조건 존재
		if (running == False) {
			share[0] = 8; //user가 먼저 끝나면(죽으면) 8로 변경해서 ai도 종료시킴
		}
		quit(0, 0, share); //score를 공유 변수에 저장
		break;
	}
	default: { //부모 프로세스 = ai
		init2();
		playAI(0, 50, share);
		if (running == False) {
			share[0] = 5;
		}
		ai_quit(0, 50, share);

		wait(&status);
	}
	}

	//share[1] = user_score, share[2] = ai_score
	if (share[1] > share[2]) { //게임이 종료되면서 저장했던 각 플레이어의 점수를 비교해서 승자를 가림
		printf("\n\n\t%s님이 이겼습니다! 점수는 %d입니다.\n\n", name, share[1]);
		exit(1);
	}
	else if (share[1] == share[2] ) { //score는 같다 누가 먼저 끝났는지 보고 승자를 가림
		printf("\n\n\t%s님과 인공지능님이 점수가 %d로 동점입니다.\n\n", name, share[1]);
		exit(1);
	}
	else { //share[1] < share[2]
		printf("\n\n\t인공지능님이 이겼습니다! 점수는 %d입니다.\n\n", share[2]);
		exit(1);
	}
	return 0;
}
