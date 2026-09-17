#include <stdio.h>
#include <windows.h>
void gotoxy(int x, int y);
int main(void)
{
    gotoxy(2, 4);
    printf("Hello");
    gotoxy(40, 20);
    printf("Hello");
    return 0;
}
void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1}; // 우리가 사용하는 좌표와 Windows 콘솔에서 사용하는 좌표가 1만큼 차이 나기 때문에 -1을 해줌
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); // 현재 프로그램의 콘솔 화면 출력 핸들
}

// 커서 위치 제어
