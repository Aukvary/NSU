#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? a : b)

typedef struct LongNum_s {
    int len; 
    char arr[3000]; 
} LongNum;

void print(const LongNum* num) {

    for (int i = 0; i < num->len; i++) {
            printf("%d", num->arr[i]);
    }
}

void add(LongNum* num1, LongNum* num2) {
    int len = MAX(num1->len, num2->len);

    num1->len = len;

    char temp = 0;

    for (int i = num1->len - 1; i > -1; i--) {
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
    num->arr[num->len++] = 0;
}

LongNum mult(LongNum* num1, LongNum* num2) {
    int len = MAX(num1->len, num2->len);

    LongNum res = {0, { 0 }};
    LongNum temp = {len, { 0 }};

    int ost = 0;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            temp.arr[j] = num1->arr[i] * num2->arr[j] + ost;
            ost = 0;
            if(temp.arr[j] > 9) {
                ost = temp.arr[j] / 10;
            }
            temp.arr[j] %= 10;
        }
        
        if (ost != 0) 
            temp.arr[temp.len++] = ost;
        
        ost = 0;
        
        for (int j = 0; j < i; j++) {
            mult10(&temp);    
        }
        add(&res, &temp);

        temp = (LongNum){ len, { 0 }};
    }

    return res;
}

LongNum newLongNum(int num) {
    if (!num) {
        return (LongNum){1, { 0 } };
    }

    LongNum new = { 0, { 0 } };

    while (num > 0) {
        new.arr[new.len++] = num % 10;
        num /= 10;
    }

    return new;
}

int main() {
    // int n;
    // scanf("%d", &n);

    // LongNum res = newLongNum(1);

    // for (int i = 2; i <= n; i++) {
    //     LongNum temp = newLongNum(i);
    //     res = mult(&res, &temp);
    // }

    LongNum v1 = newLongNum(5);
    LongNum v2 = newLongNum(16);

    add(&v1, &v2);

    print(&v1);
    printf("\n");

    return 0;
}