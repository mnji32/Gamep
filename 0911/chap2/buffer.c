#include <stdio.h>

int main()
{
    char string[20];
    char c;

    fgets(string, sizeof(string), stdin);
    // fgets는 엔터(\n)까지 저장

    scanf(" %c", &c);

    printf("%s", string);
    printf("!!%c!!\n", c);

    return 0;
}