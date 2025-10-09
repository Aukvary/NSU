#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? a : b)

typedef struct LongNum_s {
    int len; 
    char arr[3000]; 
} LongNum;

void add(LongNum* num1, LongNum* num2) {
    int len = MAX(num1->len, num2->len);

    num1->len = len;

    int temp = 0;

    for (int i = 0; i < len; i++) {
        num1->arr[i] += num2->arr[i] + temp;
        temp = 0;
        if (num1->arr[i] > 9) 
            temp = 1;
        
        num1->arr[i] %= 10;
    }
    if (temp)
        num1->arr[num1->len++] = 1;
}

void mult10(LongNum* num) {
    num->len++;
    for (int i = num->len - 1; i > 0 ; i++) {
        num->arr[i] = num->arr[i - 1];
    }

    num->arr[0] = 0;
}

LongNum mult(LongNum* num1, LongNum* num2) {
    int len = MAX(num1->len, num2->len);

    LongNum res = {0, { 0 }};
    LongNum temp = {len, { 0 }};

    int ost = 0;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            temp.arr[i] = num1->arr[i] * num2->arr[j] + ost;
            ost = temp.arr[i] - (temp.arr[i] % 10);
            temp.arr[i] %= 10;
        }

        for (int j = 0; j < i; j++) {
            mult10(&temp);    
        }
        add(&res, &temp);
    }

    return res;
}

LongNum newLongNum(int num) {
    LongNum new = {0, { 0 } };

    while (num > 0) {
        new.arr[new.len++] = num % 10;
        num /= 10;
    }
}

int main() {
    LongNum res = { 1, { 1 }};  
    
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        LongNum num = newLongNum(n + 1);
        res = mult(&res, &num);
    }

        for (int i = res.len - 1; i > -1; i--) {
        printf("%d", res.arr[i]);
    }
    
    return 0;
}