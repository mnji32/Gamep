#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

void gotoxy(int x, int y);
void set_color(int color);
void set_window_title(void);

int display_main_menu(void);
void display_rule(void);
void countdown(void);
void display_result(int count, int move_count, double pst);

void basic_map(void);
void display_map(int matrix[][11]);
void make_treasure(int tx[], int ty[]);
void make_traps(int hx[], int hy[], int tx[], int ty[]);
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b, int *valid_move);
int game_control(int tx[], int ty[], int hx[], int hy[], int *found_count);

int main(void)
{
    set_window_title();
    
    CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    while (1)
    {
        int menu_choice = display_main_menu();

        if (menu_choice == 3)
        {
            system("cls");
            set_color(15);
            printf("\n게임을 종료합니다!\n");
            break;
        }

        if (menu_choice == 2)
        {
            display_rule();
        }
        
        int tx[3], ty[3];
        int hx[2], hy[2];
        clock_t start, end;
        double pst;
        int found_count = 0; 
        
        srand((unsigned int)time(NULL));
        make_treasure(tx, ty);
        make_traps(hx, hy, tx, ty);
    
        countdown();

        system("cls");
        start = clock();
        int move_count = game_control(tx, ty, hx, hy, &found_count);
        end = clock();

        pst = (double)(end - start) / CLOCKS_PER_SEC;

        display_result(found_count, move_count, pst);

        set_color(13);
        printf("\n\n\n [ R : 다시 시작 (Restart)  |  Q : 게임 종료 (Quit) ]\n\n");

        int loop_break = 0;
        while (1)
        {
            char select = getch();
            if (select == 'r' || select == 'R')
            {
                break;
            }
            else if (select == 'q' || select == 'Q')
            {
                loop_break = 1;
                break;
            }
        }

        if (loop_break)
        {
            system("cls");
            set_color(15);
            printf("\n게임을 플레이해 주셔서 감사합니다!\n");
            break;
        }
    }

    return 0;
}

void gotoxy(int x, int y)
{
    COORD Pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void set_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
}

void set_window_title(void)
{
    SetConsoleTitle("★ 보물찾기 게임: VER 2.0 ★");
}

int display_main_menu(void)
{
    while (1)
    {
        system("cls");
        
        gotoxy(2, 1); set_color(8);
        printf("GAME PROGRAMMING  |  DATE: 2026.11.06  |  VERSION: 2.0");
        
        set_color(14); gotoxy(9, 3); 
		printf(" ___  ___  ___    _   ___  _   _  ___  ___   _  _ _   _ _  _ _____");
        gotoxy(9, 4); printf("|_ _|| _ \\| __|  /_\\ / __|| | | || _ \\| __| | || | | | | \\| |_  _|");
        set_color(6);
        gotoxy(9, 5); printf(" | | |   /| _|  / _ \\\\__ \\| |_| ||   /| _|  | __ | |_| |\\   | | |  ");
        gotoxy(9, 6); printf(" |_| |_|_\\|___|/_/ \\_\\___/ \\___/ |_|_\\|___| |_||_|\\___/|_|\\_| |_|  ");

        set_color(11); gotoxy(23, 9);
        printf("★ 숨겨진 보물을 찾아라! ★");

        set_color(13); gotoxy(5, 11);
        printf("┌───────────────────────────────────────────────────────────────┐");
        for (int i = 12; i <= 18; i++) {
            gotoxy(5, i);
			printf("│                                                               │");
        }
        gotoxy(5, 19); printf("└───────────────────────────────────────────────────────────────┘");

        set_color(15); gotoxy(18, 13);
        printf(" [ 1 ]  ▶   게 임 시 작  (Start Game)");
        
        gotoxy(18, 15);
        printf(" [ 2 ]  ▶   게 임 설 명  (Game Rules)");
        
        gotoxy(18, 17); set_color(12);
        printf(" [ 3 ]  ▶   게 임 종 료  (Exit Game)");

        set_color(10); gotoxy(16, 21);
        printf("▶ 원하는 메뉴의 번호 [ 1 ~ 3 ] 키를 누르세요: ");
        
        char ch = getch();
        if (ch == '1') return 1;
        if (ch == '2') return 2;
        if (ch == '3') return 3;
    }
}

void display_rule(void)
{
    system("cls");

    gotoxy(4, 2); set_color(7);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    gotoxy(4, 3); set_color(7);
    printf("                      게임 설명 & 조작 방법                    ");
    gotoxy(4, 4); set_color(7);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");

    gotoxy(6, 6); set_color(11); printf("▶  미션 목표");
    gotoxy(8, 7); set_color(7); printf("- 10x10 격자에 숨겨진 ");
    set_color(14); printf("3개");
    set_color(7); printf("의 보물을 모두 획득하세요.");
    gotoxy(8, 8); set_color(7); printf("- 주어진 ");
    set_color(14); printf("이동 횟수");
    set_color(7); printf(" 이내에 모아야 탐험 성공!");

    gotoxy(6, 10); set_color(11); printf("▶  특수 요소");
    gotoxy(8, 11); set_color(12); printf(" 함정 [X]");
    set_color(7); printf(" : 밟으면 3초간 이동 불가");
    gotoxy(8, 12); set_color(14); printf(" 힌트 [H]");
    set_color(7); printf(" : 남은 보물까지 거리 탐지 (최대 3회)");

    gotoxy(6, 14); set_color(11); printf("▶  점수 산출 공식");
    gotoxy(8, 15); set_color(7); printf(" (남은 이동 횟수 × 20점) - (소요 시간 × 2점)");
    gotoxy(8, 16); set_color(13); printf(" S+"); set_color(7); printf(" : 1,100점 이상   ");
    set_color(14); printf(" S"); set_color(7); printf(" : 850점 이상");
    gotoxy(8, 17); set_color(10); printf(" A "); set_color(7); printf(" :   500점 이상   ");
    set_color(10); printf(" B"); set_color(7); printf(" : 500점 미만 (실패 시 F)");
    // ------------------------------------

    gotoxy(6, 19); set_color(11); printf("▶  조작 방법");
    gotoxy(8, 20); set_color(15); printf(" 이동 : "); set_color(7); printf("방향키  또는  W, A, S, D");
    gotoxy(8, 21); set_color(15); printf(" 힌트 : "); set_color(7); printf("H 키 (보물 거리 힌트 차감)");
    gotoxy(8, 22); set_color(15); printf(" 정지 : "); set_color(7); printf("ESC 키");

    gotoxy(4, 24); set_color(8);
    printf("-------------------------------------------------------------------");
    gotoxy(14, 26); set_color(11);
    printf("▶ 아무 키나 누르면 카운트다운 후 게임이 시작됩니다 ◀");

    getch();
}

void countdown(void)
{
    system("cls");
    gotoxy(1, 4);
    set_color(15);
    printf("     게임을 준비하는 중입니다...\n\n");

    for (int i = 3; i >= 1; i--)
    {
        gotoxy(1, 6);
        set_color(11);
        printf("               %d           ", i);
        Sleep(500);
    }

    gotoxy(1, 6);
    set_color(12);
    printf("             START!             ");
    Beep(1047, 300); 
    Sleep(300);
}

void display_result(int count, int move_count, double pst)
{
    system("cls");

    int minutes = (int)pst / 60;
    int seconds = (int)pst % 60;

    int remaining_moves = 75 - move_count;
    if (remaining_moves < 0) remaining_moves = 0;
    int score = (remaining_moves * 20) - (int)(pst * 2);
    if (score < 0) score = 0;
    
    char rank[5];
    int rank_color = 15;

    if (count < 3) {
        strcpy(rank, "F");
        rank_color = 12;
    } else if (score >= 1100) {
        strcpy(rank, "S+");
        rank_color = 13;
    } else if (score >= 850) {
        strcpy(rank, "S");
        rank_color = 14;
    } else if (score >= 500) {
        strcpy(rank, "A");
        rank_color = 10;
    } else {
        strcpy(rank, "B");
        rank_color = 10;
    }

    gotoxy(1, 2); set_color(8);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    
    gotoxy(1, 3);
    if (count >= 3)
    {
        set_color(14);
        printf("                  ★ GAME CLEAR : 보물 찾기 성공 ★                   ");
    }
    else
    {
        set_color(12);
        printf("                  ★ GAME OVER : 보물 찾기 실패 ★                    ");
    }

    gotoxy(1, 4); set_color(8);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    
    gotoxy(1, 6); set_color(11);
    printf(" [ 보물찾기 결과 리포트 ]");
    
    gotoxy(1, 8); set_color(15); printf("   총 소요 시간  :  ");
    set_color(7); printf("%d분 %d초", minutes, seconds);

    gotoxy(1, 9); set_color(15); printf("   총 이동 횟수  :  ");
    set_color(7); printf("%d / 75 회", move_count);

    gotoxy(1, 10); set_color(15); printf("   획득한 보물   :  ");
    set_color(7); printf("%d / 3 개", count);

    gotoxy(1, 12); set_color(14);
    printf("   최종 산출 점수"); 
    set_color(15); printf("  :  %d 점 ", score);

    set_color(rank_color);
    printf("[ %s 등급 ]", rank);
}

void basic_map(void)
{
    int i, j;
    
    for (i = 0; i < 10; i++)
    {
        gotoxy(5, i + 6);
        set_color(15);
        for (j = 0; j < 10; j++)
        {
            printf("■ ");
        }
    }
}

void display_map(int matrix[][11])
{
    int i, j;
    basic_map(); 
    for (i = 1; i <= 10; i++)
    {
        for (j = 1; j <= 10; j++)
        {
            if (matrix[i][j] == 1)
            {
                gotoxy(2 * i + 3, j + 5);
                set_color(15);
                printf("□");
            }
            else if (matrix[i][j] == 2)
            {
                gotoxy(2 * i + 3, j + 5);
                set_color(14);
                printf("★");
            }
            else if (matrix[i][j] == 3)
            {
                gotoxy(2 * i + 3, j + 5);
                set_color(12);
                printf("X ");
            }
        }
    }
}

void make_treasure(int tx[], int ty[])
{
    for (int i = 0; i < 3; i++)
    {
        do {
            tx[i] = rand() % 10 + 1;
            ty[i] = rand() % 10 + 1;
        } while ((i == 1 && tx[1] == tx[0] && ty[1] == ty[0]) ||
                 (i == 2 && ((tx[2] == tx[0] && ty[2] == ty[0]) || (tx[2] == tx[1] && ty[2] == ty[1]))));
    }
}

void make_traps(int hx[], int hy[], int tx[], int ty[])
{
    for (int i = 0; i < 2; i++)
    {
        do {
            hx[i] = rand() % 10 + 1;
            hy[i] = rand() % 10 + 1;
        } while ((hx[i] == tx[0] && hy[i] == ty[0]) ||
                 (hx[i] == tx[1] && hy[i] == ty[1]) ||
                 (hx[i] == tx[2] && hy[i] == ty[2]) ||
                 (hx[i] == 1 && hy[i] == 1) ||
                 (i == 1 && hx[1] == hx[0] && hy[1] == hy[0]));
    }
}

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b, int *valid_move)
{
    *valid_move = 1;
    int prev_x = *x1;
    int prev_y = *y1;
    
    switch (key)
    {
    case 72: case 'w': case 'W':
        *y1 = *y1 - 1;
        if (*y1 < 1) *y1 = 1;
        break;
    case 75: case 'a': case 'A':
        *x1 = *x1 - 2;
        if (*x1 < 1) *x1 = 1;
        break;
    case 77: case 'd': case 'D':
        *x1 = *x1 + 2;
        if (*x1 > x_b) *x1 = x_b;
        break;
    case 80: case 's': case 'S':
        *y1 = *y1 + 1;
        if (*y1 > y_b) *y1 = y_b;
        break;
    default:
        *valid_move = 0;
        gotoxy(1, 22); set_color(12);
        printf("[경고] 잘못된 입력입니다! (방향키, WASD, H, ESC만 가능)                    "); 
        return; 
    }
    
    if (prev_x == *x1 && prev_y == *y1) {
        *valid_move = 0;
    }
    else {
        gotoxy(1, 22);
        printf("                                                                            ");
    }
}

int game_control(int tx[], int ty[], int hx[], int hy[], int *found_count)
{
    char key;
    int i, j, count = 0;
    int move_count = 0;
    int max_moves = 75;
    int hint_count = 3;
    int x = 1, y = 1;
    int matrix[11][11] = { 0 };

    display_map(matrix);

    do
    {
        int grid_x = (x + 1) / 2;
        int grid_y = y;

        if (matrix[grid_x][grid_y] == 0)
        {
            matrix[grid_x][grid_y] = 1;
            
            for (i = 0; i < 3; i++)
            {
                if (grid_x == tx[i] && grid_y == ty[i])
                {
                    matrix[grid_x][grid_y] = 2;
                    
                    Beep(784, 120);
                    Beep(1047, 200);
                }
            }
            
            for (i = 0; i < 2; i++)
            {
                if (grid_x == hx[i] && grid_y == hy[i])
                {
                    matrix[grid_x][grid_y] = 3;
                    
                    gotoxy(1, 22);
                    set_color(12);
                    printf("[함정] 발이 묶였습니다! (3초간 이동할 수 없습니다)                        ");
                    Beep(200, 300);
                    Sleep(3000);
                    
                    gotoxy(1, 22);
                    printf("                                                                            ");
                }
            } 
        }

        gotoxy(2 * grid_x + 3, grid_y + 5);
        set_color(10);
        printf("&");

        count = 0;
        for (i = 1; i <= 10; i++)
            for (j = 1; j <= 10; j++)
                if (matrix[i][j] == 2)
                    count++;
                    
        *found_count = count;

        gotoxy(1, 1); set_color(14);
        printf("━━━━━━━━━━━━━━━━ 보물찾기 게임 : VER 2.0 ━━━━━━━━━━━━━━━━━━━━");

        gotoxy(1, 2); set_color(15);
        printf(" [위치] X:%2d, Y:%2d | ", grid_x, grid_y);
        
        if (max_moves - move_count <= 10) set_color(12);
        else set_color(15);
        printf("[이동] %2d / %2d 회", move_count, max_moves);
        
        set_color(15);
        printf(" | [힌트] %d / 3 회", hint_count);
        
        gotoxy(1, 3); set_color(11);
        printf(" [보물 진행도] ");
        set_color(15);
        if (count == 0) printf("☆ ☆ ☆ ");
        else if (count == 1) printf("★ ☆ ☆ ");
        else if (count == 2) printf("★ ★ ☆ ");
        else printf("★ ★ ★ ");
        printf(" (%d / 3개 발견)                               ", count);

        gotoxy(1, 19); set_color(8);
        printf("-----------------------------------------------------------------------");
        gotoxy(1, 20); set_color(7);
        printf("[조작] 이동: 방향키 / WASD  |  힌트: H  |  일시정지: ESC");

        if (count >= 3)
        {
            gotoxy(1, 22);
            set_color(10);
            printf(" GAME CLEAR - 모든 보물을 찾아냈습니다!                                    \n");
            Beep(523, 120);
            Beep(659, 120);
            Beep(784, 120);
            Beep(1047, 350);
            break;
        }
        
        if (move_count >= max_moves)
        {
            gotoxy(1, 22);
            set_color(12);
            printf("GAME OVER - 이동 횟수를 모두 소진했습니다!                                \n");
            Beep(300, 250);
            Beep(200, 400);
            break;
        }

        key = getch();

        gotoxy(2 * grid_x + 3, grid_y + 5);
        if (matrix[grid_x][grid_y] == 2) {
            set_color(14);
            printf("★");
        }
        else if (matrix[grid_x][grid_y] == 3) {
            set_color(12);
            printf("X ");
        }
        else {
            set_color(8);
            printf("□");
        }

        if (key == 27)
        {
            gotoxy(1, 22);
            set_color(10);
            printf("[일시정지] 1: 계속하기 / 2: 게임종료                                    ");
            char select = getch();
            if (select == '2')
            {
                exit(0);
            }
            gotoxy(1, 22);
            printf("                                                                            ");
        }
        else if (key == 'h' || key == 'H')
        {
            if (hint_count > 0)
            {
                hint_count--;
                
                int target_idx = -1;
                for (i = 0; i < 3; i++)
                {
                    if (matrix[tx[i]][ty[i]] != 2)
                    {
                        target_idx = i;
                        break;
                    }
                }

                gotoxy(1, 22); set_color(11);
                if (target_idx != -1)
                {
                    int dist = abs(grid_x - tx[target_idx]) + abs(grid_y - ty[target_idx]);
                    printf("[힌트] 남은 보물까지 거리 약 %d칸! (남은 힌트: %d / 3회)        ", dist, hint_count);
                    Beep(800, 150);
                }
            }
            else
            {
                gotoxy(1, 22); set_color(15);
                printf("힌트를 모두 사용하셨습니다! (남은 힌트: 0/3회)                            ");
                Beep(250, 200);
            }
        }
        else
        {
            int valid_move = 0;
            if (key == -32 || key == 0)
            {
                key = getch();
                move_arrow_key(key, &x, &y, 19, 10, &valid_move);
            }
            else
            {
                move_arrow_key(key, &x, &y, 19, 10, &valid_move);
            }

            if (valid_move)
            {
                move_count++;
            }
        }

    } while (1);
    
    return move_count;
}
