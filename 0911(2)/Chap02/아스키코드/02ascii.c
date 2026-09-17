#include <stdio.h>
#include <conio.h>

int main(void)
{
    int chr;

    do
    {
        chr = getch();
        
        if (chr == 0 || chr == 0xe0)
        {
            chr = getch();
            printf("확장키 code=%d\n", chr);
        }
        else
        {
            printf("아스키 code=%d\n", chr);
        }
    } while(1);

    return 0;
}

// 방향키 및 일반 키 코드 구분 처리
