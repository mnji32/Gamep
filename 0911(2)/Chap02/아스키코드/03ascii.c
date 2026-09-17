#include <stdio.h>
#include <conio.h> 
#include <windows.h>

#define X_MAX 79 // 콘솔 가로 화면의 최대 크기 
#define Y_MAX 24 // 콘솔 세로 화면의 최대 크기

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);

int main(void)
{
    char key;
    int x = 10, y = 5;
    
    do
    {
        gotoxy(x, y);
        printf("A");

        key = getch();
        
        move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
    } while (key != 27);
    return 0;
}

void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 입력된 키 코드에 따라 좌표 값 변경 (포인터로 원본 값 수정)
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
    switch (key)
    {
        case 72: // 위쪽(↑) 방향키 입력 
            *y1 = *y1 - 1;
            if (*y1 < 1) *y1 = 1; // y좌표의 최소값
            break;
        case 75: // 왼쪽(←) 방향키 입력 
            *x1 = *x1 - 1;
            if (*x1 < 1) *x1 = 1; // x좌표의 최소값
            break;
        case 77: // 오른쪽(→) 방향키 입력 
            *x1 = *x1 + 1;
            if (*x1 > x_b) *x1 = x_b; // x좌표의 최대값
            break;
        case 80: // 아래쪽(↓) 방향키 입력 
            *y1 = *y1 + 1;
            if (*y1 > y_b) *y1 = y_b; / // y좌표의 최대값
			break;
		default:
			return;
    }
}

// A글자 띄우고 방향키로 움직이기
