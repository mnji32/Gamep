#include <stdio.h>

int main()
{
    char string[20];
    char c;

    fgets(string, sizeof(string), stdin);
    // 엔터(\n)까지 저장

    scanf(" %c", &c);
    // 앞에 공백을 넣어 \n을 건너뜀 
    
    printf("%s", string);
    printf("!!%c!!\n", c);

    return 0;
}

// C언어 문자열 및 문자 연속 입력 처리
