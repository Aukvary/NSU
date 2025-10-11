#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? a : b)

typedef struct LongNum_s {
    int len; 
    char arr[3000]; 
} LongNum;

void print(const LongNum* num) {
    char zeros = 1;

    for (int i = num->len - 1; i > -1; i--) {
        if (zeros && num->arr[i] != 0)
            zeros = 0;

        if (!zeros)
            printf("%d", num->arr[i]);
    }
    printf("\n");
}

void mult(LongNum* num, int multiplier) {
    int carry = 0;
    
    for (int i = 0; i < num->len; i++) {
        int product = num->arr[i] * multiplier + carry;
        num->arr[i] = product % 10;
        carry = product / 10;
    }
    
    while (carry > 0) {
        num->arr[num->len++] = carry % 10;
        carry /= 10;
    }
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
    int n;
    scanf("%d", &n);

    LongNum res = newLongNum(1);

    for (int i = 2; i <= n; i++) {
        mult(&res, i);
    }

    print(&res);

    return 0;
}