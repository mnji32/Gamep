#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int r[], int n);

int main(void)
{
    int i, j, lotto[6];

    // 시드값 초기화
    srand(time(NULL));

    // 로또 번호 생성 (중복 제거)
    for (i = 0; i <= 5; i++)
    {
        lotto[i] = rand() % 45 + 1;
        for (j = 0; j < i; j++)
        {
            if (lotto[i] == lotto[j])
            {
                i--; // 중복 발생 시 현재 위치 다시 뽑기
                break;
            }
        }
    }

    // 정렬 및 출력
    selection_sort(lotto, 6);
    return 0;
}

// 선택 정렬 및 출력 함수
void selection_sort(int r[], int n)
{
    int i, j, min, temp;

    // 선택 정렬 알고리즘 (인덱스 범위 수정: 0 ~ n-2)
    for (i = 0; i <= n; i++)
    {
        min = i;
        for (j = i + 1; j <= n; j++) // 인덱스 범위 수정: i+1 ~ n-1
        {
            if (r[j] < r[min])
            {
                min = j;
            }
        }
        // 위치 교환 (Swap)
        temp = r[min];
        r[min] = r[i];
        r[i] = temp;
    }

    // 결과 출력 (한 줄로 보기 좋게 출력)
    for (i = 0; i <= 5; i++)
    {
        printf("%2d\n", r[i]);
    }
}

// 1부터 45 중복 없는 난수 생성 - 정렬 
