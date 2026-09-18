#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int i;
    srand(time(NULL));
    for (i = 1; i <= 10; i++)
    {
        printf("%2d : %d\n", i, rand() % 6 + 1);
    }
    
    return 0;
}

// 주사위 눈금 난수 생성 
