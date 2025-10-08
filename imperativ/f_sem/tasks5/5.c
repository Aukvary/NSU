#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? a : b)

typedef struct LongNum_s {
    int len; // сколько цифр в числе
    int arr[500]; // массив десятичных цифр числа
} LongNum;

LongNum sum(LongNum* num1, LongNum* num2) {
    int len = MAX(num1->len, num2->len);

    LongNum res = { len, { 0 }};

    int temp = 0;

    for (int i = 0; i < len; i++) {
        res.arr[i] = num1->arr[i] + num2->arr[i] + temp;
        temp = 0;
        if (res.arr[i] > 9) 
            temp = 1;
        
        res.arr[i] %= 10;
    }
    if (temp)
        res.arr[res.len++] = 1;

    return res;
}

int main() {
    LongNum prev = { 1, { 1 }};
    LongNum cur = { 1, { 1 }};    
    
    int n;
    scanf("%d", &n);

    for (int i = 3; i <= n; i++) {
        LongNum temp = cur;
        cur = sum(&cur, &prev);
        prev = temp;
    }

    for (int i = cur.len - 1; i > -1; i--) {
        printf("%d", cur.arr[i]);
    }
    
    return 0;
}