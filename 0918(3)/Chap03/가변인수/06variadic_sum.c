#include <stdio.h>
#include <stdarg.h>

double sum(int count, ...);

int main(void) 
{
    printf("합계 = %lf\n", sum(2, 10.5, 20.23));
    printf("합계 = %lf\n", sum(4, 10.3, 245.67, 0.51, 198345.764));
    return 0;
}

double sum(int count, ...)
{
    double total = 0, number;
    int i = 0;
    va_list ap; // 가변 인자 목록을 가리킬 포인터 변수 선언 
    va_start(ap, count); // ap가 count 바로 뒤의 첫번째 가변인자를 가리키도록 초기화 
    while (i < count)
    {
        number = va_arg(ap, double); // ap위치에서 double 타입 데이터를 하나 읽어오고, ap를 다음 인자 위치로 이동 
        total += number;
        i++;
    }

    va_end(ap); 

    return total;
}

// 가변 인자를 활용한 실수 합계 구하기
