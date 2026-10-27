## 10월 02일 수업 내용

### 1. 음계 제어 및 콘솔 피아노 구현

#### 1) `Beep()` 함수 개념
Windows OS 환경에서 메인보드의 피조 스피커(Buzzer) 또는 기본 사운드 장치를 통해 **지정한 주파수와 시간** 동안 소리를 출력하는 Win32 API 함수

- **함수 원형**: `BOOL WINAPI Beep(DWORD dwFreq, DWORD dwDuration);`

| 매개변수 | 타입 | 설명 |
| :--- | :--- | :--- |
| **`dwFreq`** | `DWORD` | 출력할 소리의 주파수 (Hz 단위, **37Hz ~ 32,767Hz** 범위 지정) |
| **`dwDuration`** | `DWORD` | 소리가 유지될 지속 시간 (**밀리초 / ms** 단위, 예: 500 = 0.5초) |

---

#### 2) 음계 및 옥타브별 주파수 계산 알고리즘

- **기준 주파수**: 1옥타브 '도(C)'의 주파수 = **$32.7032\text{ Hz}$**
- **옥타브 비**: 1옥타브가 올라갈 때마다 주파수가 **2배** 증가 ($2^{\text{octave}-1}$)
- **반음 간격 비**: 1옥타브는 12개의 반음으로 구성되며, 각 반음 간의 주파수 비율은 $2^{1/12} \approx 1.05946$

---

### 2. 자료구조 및 알고리즘
#### 1) 자료구조의 분류 및 동적 메모리

| 구분 | 구조형태 | 대표적인 자료구조 |
| :--- | :--- | :--- |
| **선형구조** | 데이터가 일렬로 연속되게 연결 | 연결 리스트, 스택, 큐, 덱 |
| **비선형 구조** | 데이터가 1:N 또는 N:M 구조 | 트리, 그래프 |

- 동적 메모리 할당: 실행 중에 필요한 만큼만 메모리를 할당(malloc)하고 사용 후 해제(free)하여 정적 배열의 공간 낭비 문제 극복

#### 2) 단순 연결 리스트
#### ① 노드 구조 및 게임 리플레이 시스템 활용
- 데이터 필드 + 링크 포인터 필드로 구성
- 게임 중 키 입력을 연결 리스트에 순서대로 저장하여 head 포인터부터 순회하면 리플레이 기능 구현 가능

```c
struct linked_list {
    char data;
    struct linked_list *link;
};
struct linked_list *head = NULL;

// 노드 추가 함수
void add_node(char data) {
    struct linked_list *new_node = (struct linked_list*)malloc(sizeof(struct linked_list));
    struct linked_list *now = head;

    new_node->data = data;
    new_node->link = NULL;

    while (now->link != NULL) {
        now = now->link;
    }
    now->link = new_node;
}

// 재귀를 이용한 역순 출력
void print_reverse_linked_list(struct linked_list *now) {
    if (now == NULL) return;
    print_reverse_linked_list(now->link);
    printf("%c ", now->data);
}
```

#### 3) 스택
- LIFO (Last-In, First-Out): 가장 나중에 들어온 데이터가 먼저 나가는 구조

```c
struct stack_node {
    char data;
    struct stack_node *link;
};
struct stack_node *top = NULL;

void push(char data) {
    struct stack_node *new_node = (struct stack_node*)malloc(sizeof(struct stack_node));
    new_node->data = data;
    new_node->link = top;
    top = new_node;
}

char pop(void) {
    if (top == NULL) return '\0';
    struct stack_node *temp = top;
    char data = temp->data;
    top = top->link;
    free(temp);
    return data;
}
```
#### 4) 문자열 데이터 정렬
- ASCII 코드 특성상 대문자 'A'(65)가 소문자 'a'(97)보다 작은 값을 가짐
- 알파벳순 정렬을 위해 정렬 비교 시에만 대문자를 소문자로 변환하여 알파벳 순서를 맞춰 정렬
