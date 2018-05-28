/*
 * tetris_user.c
 *
 *  Created on: 2018. 5. 27.
 *      Author: kny
 */
#include "tetris.h"
#include "config.h"

/* Functions */

char* first(char * name) {

    char start;
    printf("\n\n\t당신의 이름은? ");
    scanf("%s", name);
    //printf("\n\n\t\t\tpress enter to enter game!");     //tab세번이 적절
 /*   while (1) {
        start = getchar();
        if (start == '\n')
            break;
    }*/
    return name;
}
void init_user(void) {

    struct sigaction siga;
    struct termios term;

    /* Clean term */
    clear_term();
    set_cursor(False);
    /* Init terminal (for non blocking & noecho getchar();
     이것을 위로 옮긴 이유는 처음부터 껌벅커서를 지우기 위해*/
    tcgetattr(STDIN_FILENO, &term);
    tcgetattr(STDIN_FILENO, &back_attr);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
    /*스타트함수를 init에 통합했다*/
    //set_cursor(False); //커서없애줌
 /*   printxy(0, FRAMEH_NB + 2, FRAMEW + 3, "Score :");
    printxy(0, FRAMEH_NB + 3, FRAMEW + 3, "Lines :");
    printxy(0, FRAMEH_NB + 4, FRAMEW + 3, "Left  : ←");
    printxy(0, FRAMEH_NB + 5, FRAMEW + 3, "Right : →");
    printxy(0, FRAMEH_NB + 6, FRAMEW + 3, "Change: ↑");
    printxy(0, FRAMEH_NB + 7, FRAMEW + 3, "Down  : ↓");
    printxy(0, FRAMEH_NB + 8, FRAMEW + 3, "Drop  : Space Bar");
    printxy(0, FRAMEH_NB + 9, FRAMEW + 3, "Pause : p");
    printxy(0, FRAMEH_NB + 10, FRAMEW + 3, "Revive : r");
    printxy(0, FRAMEH_NB + 11, FRAMEW + 3, "Quit  : q");*/
    //게임 시작하기 전에 안내를 한번 해줌

   // clear_term(); //화면 지움
    /* Make rand() really random :)
    srand(getpid());*/

    /* Init variables */
    score1 = 0;

    running1 = True;    //true일 경우에 게임의 축이 되는 루프가 계속 돌아가고 false일 경우 루프가 break되고 quit함수가 호출되어 종료된다
    finish1 = False;
    current1.y = (FRAMEW / 2) - 1;
    current1.num = nrand(0, 7); //7가지블록랜덤
    current1.next = nrand(0, 7); //다음 블록의 종류를 정함

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
    DRAW_SCORE1();

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
        --current1.x;
    /*main함수중에 전체 루프중에 필수적으로 거치는 함수이자 입력받은 값에따라 게임 진행이 된다.
     여기서 key_pause와 key_quit는 게임을 계속 진행하는 대에 영향을 준다*/
    switch (c) {
    case KEY_MOVE_LEFT:
        shape_move_user(-EXP_FACT);
        break;
    case KEY_MOVE_RIGHT:
        shape_move_user(EXP_FACT);
        break;
    case KEY_MOVE_DOWN:
        ++current1.x;
        ++score1;
        DRAW_SCORE1();
        break;
    case KEY_CHANGE_POSITION_NEXT:
        shape_set_position_user(N_POS);
        break;
    case KEY_DROP_SHAPE:
        shape_drop_user();
        break;
    case KEY_PAUSE:
        while (getchar() != KEY_PAUSE)
            ;
        break;
    case KEY_QUIT:
        running1 = False;
        break;
    case 'Q':
        running1 = False;
        break; //대문자 Q를 사용할 때 종료
    case 'r':
        if (lifes1 != 0)
            revive_user();
        break;
        //case 't':                      sleep(5);                         break; //5초 정지
        //시간 멈추는 능력
    }

    return;
}

void arrange_score_user(int l) {
    /* 클리어한 라인에따라 점수부여. 여기서 의문점이 5줄이상일때 에러가 발생하는지
     테트리스는 5줄이상 못깹니다.  */
    switch (l) {
    case 1:
        score1 += 40;
        break; /* One line */
    case 2:
        score1 += 100;
        break; /* Two lines */
    case 3:
        score1 += 300;
        break; /* Three lines */
    case 4:
        score1 += 1200;
        break; /* Four lines */
    }

    if (score1 >= 100)  //레벨 추가
        level1 = 2;
    if (score1 >= 400)
        level1 = 3;
    if (score1 >= 700)
        level1 = 4;
    if (score1 >= 1000)
        level1 = 5;
    lines1 += l;

    DRAW_SCORE1();

    return;
}

void check_plain_line_user(void) {
    int i, j, k, f, c = 0, nl = 0;

    for (i = 1; i < FRAMEH; ++i) {
        for (j = 1; j < FRAMEW; ++j)
            if (frame1[i][j] == 0)
                ++c;
        if (!c) {
            ++nl;
            for (k = i - 1; k > 1; --k)
                for (f = 1; f < FRAMEW; ++f)
                    frame1[k + 1][f] = frame1[k][f];
        }
        c = 0;
    }
    arrange_score_user(nl);
    frame_refresh_user();

    return;
}

int check_possible_pos_user(int x, int y) {
    int i, j, c = 0;

    for (i = 0; i < 5; ++i)
        for (j = 0; j < EXP_FACT; ++j)
            if (frame1[x + shapes1[current1.num][current1.pos][i][0]][y
                    + shapes1[current1.num][current1.pos][i][1] * EXP_FACT + j]
                    != 0)
                ++c;

    return c;
}

void quit_user(char * name) {
    FILE *rp;
    rp = fopen("score.txt", "a+");
    int best_sc;
    fscanf(rp, "%d", &best_sc);

    char end;
    frame_refresh_user(); /* Redraw a last time the frame */

    set_cursor(True); //이 함수로인해 터미널창 커서가 숨김에서 풀린다
    tcsetattr(0, TCSANOW, &back_attr); //TCSANOW는 즉시속성을 변경을 의미,

    if (best_sc < score1) {
        printf("\n\n\n%d ", best_sc);
        if (best_sc != 0) {
            FILE *wp;
            wp = fopen("score.txt", "w");
            fprintf(wp, "%d %s", score1, name);
            fclose(wp);
        } else {
            fprintf(rp, "%d %s", score1, name);
            printf("\n\n\nsad");
        }
        printf("\n\n\t축하합니다. %s님이 레벨 %d, 최고점수 %d 점을 달성했습니다.\n\n", name, level1, score1);
    } else {
        printf("\n\n\t수고하셨습니다. %s님의 레벨 %d, 점수는: %d입니다.\n\n", name, level1, score1);
    }
    fclose(rp);

/*    printf("\n\n\t\t\tpress enter to end the game!\n");
    while (1) {
        end = getchar();
        if (end == '\n')
            break;
    }*/
    set_cursor(True);
    tcsetattr(0, TCSANOW, &back_attr); //TCSANOW는 즉시속성을 변경을 의미, 터미널 세팅을 되돌리기
    system("clear"); //입력창이 다 밑으로 내려가서 이걸로하면 다시위로감

    finish1 = True;
    return;
}

void playUser() {

   // int n = 1;
    //여기까지 게임을 초기화하는 부분

        int ranNum = nrand(1, 300);

        get_key_event();
        shape_set_user();
        if (score1 < 2000)       //레벨 5가 되면 블록이 안보임
         {
            frame_refresh_user();
            frame_preview_user();
        }

        shape_go_down_user();

        if (score1 > 2000)
            printxy(0, FRAMEH_NB + 13, FRAMEW + 3, "***블록이 안보입니다***");

     /*   if (n >= 1 && score1 >= 100) {*/
        if (score1 >= 100) {
         //   n--;
            block_down_user();
        }

      /*  if (ranNum == 108)
            n++;*/
        //이것이 게임루프의 주축이 되는 부분
}





