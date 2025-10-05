#include <stdio.h>

#define DIGIT(c) (c >= '0' && c <= '9')
#define TO_INT(c) (c - '0')
#define SIZE 10000

int readTime(char* str, int* h, int* m, int* s) {
    int i = 0;

    for (; str[i] != ':' && str[i] != '\0' && str[i] != '\n'; i++) {
        if (!DIGIT(str[i])) return 0;
        *h *= 10;
        *h += TO_INT(str[i]);
    }

    if (*h > 23 || *h < 0) 
        return 0;

    if (!m)
        return 1;

    i++;
    
    for (; str[i] != ':' && str[i] != '\0' && str[i] != '\n'; i++) {
        if (!DIGIT(str[i])) return 0;
        *m *= 10;
        *m += TO_INT(str[i]);
    }

    if (*m > 59) 
        return 0;

    if (!s)
        return 1;

    i++;

    for (; str[i] != '\0' && str[i] != '\n'; i++) {
        if (!DIGIT(str[i])) return 0;
        *s *= 10;
        *s+= TO_INT(str[i]);
    }

    return *s > 59 ? 0 : 1;
}

int main() {
    char buf[SIZE];
    fgets(buf, SIZE, fopen("input.txt", "r"));

    int h = 0;
    int m = 0;
    int s = 0;

    int res = readTime(buf, &h, &m, &s);

    if (res) {
        printf("%d %d %d %d\n", res, h, m, s);
        printf("%d %d %d\n", res, h, m);
        printf("%d %d\n", res, h);

    } else {
        printf("0 -1 -1 -1\n");
        printf("0 -1 -1\n");
        printf("0 -1\n");
    }


    return 0;
}