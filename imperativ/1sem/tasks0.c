#include <stdio.h>

void t0_task1() {
    printf("Hello, World!\n");
}

void t0_task2() {
    int a;
    int b;

    scanf("%d %d", &a, &b);

    printf("%d\n", a + b);
}

void t0_task3() {
    int a;
    int b;

    scanf("%d %d", &a, &b);

    printf("%d\n", a * b);

    if (b == 0) printf("divining by zero exception: b was 0 ");
    else printf("%d ", a % b);

    if (a == 0) printf("divining by zero exception: a was 0\n");
    else printf("%d\n", b % a);
}

void t0_task4() {
    int a;
    int b;

    scanf("%d %d", &a, &b);
    
    if (b == 0) printf("divining by zero exception: b was 0\n");
    else printf("%d\n", a / b);

    printf("%0.2f\n", (float)(a + b) / 2);
}

void t0_task5() {
    int a;
    int res;

    scanf("%d", &a);

    for (int i = 1; i <= a; i++)
        res += i;

    printf("%d\n", res);
}