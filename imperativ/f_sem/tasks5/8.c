#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? a : b)

typedef struct {
    int len;
    char arr[101];
} LongNum;

LongNum newLongNum(int val) {
    LongNum num = {0, { 0 }};

    if (!val) {
        num.len++;
        return num;
    }

    while (val) {
        num.arr[num.len++] = val % 10;
        val /= 10;
    }

    return num;
}

LongNum sum(const LongNum* v1, const LongNum* v2) {
    int len = MAX(v1->len, v2->len);
    LongNum num = { len, { 0 } };

    char ost = 0;

    for (int i = 0; i < len; i++) {
        num.arr[i] = v1->arr[i] + v2->arr[i] + ost;
        ost = num.arr[i] > 10;
        num.arr[0] %= 10; 
    }

    if (ost) {
        num.arr[num.len++] = 1;
    }

    return num;
}

LongNum sub(const LongNum* v1, const LongNum* v2) {

}

LongNum mult(const LongNum* v1, int v2) {

}

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;
    fscanf(in, "%d\n", &n);

    LongNum* nums = calloc(sizeof(LongNum), n);
    char buf[200];

    for (int i = 0; fgets(buf, sizeof(buf), in); i++) {
        char* mode = strtok(buf, " \n\0");

        switch (mode[0]) {
            case '0':
                break;

            case '1':
                break;

            case '2':
                break;
            case '3':
                break;
        }
    }

    return 0;
}