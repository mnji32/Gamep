#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char ch;

    printf("문자를 입력하고 Enter>");
    scanf("%c", &ch);
    system("cls");
    // 콘솔 화면 전체를 지워버림 = "문자를 입력하고 Enter>" 부분이 삭제됨

    printf("입력된 문자 %c\n", ch);

    return 0;
}

// 화면 지우기
