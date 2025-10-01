#include <stdio.h>

#define SIZE 1000000

int main() {
    FILE* in = fopen("input.txt", "r");
    char buf[SIZE] = { 0 };
    char ch = 0;
    int bp = 0;
    int h = 0;
    int c = 0;
    for (int i = 0; (ch = fgetc(in)) != EOF; i++) {
        if (ch == '.' || ch == ',' || ch == ':' || ch == ';' || ch == '\0' || ch == '\n') {
            if (c > 0)
                printf("%d/%d %s\n", h, c, buf);

            for (int j = 0; j < bp; j++)
                buf[j] = 0;
            h = 0;
            c = 0;
            bp = 0;
            continue;
        }
        c++;
        if (ch >= 'A' && 'Z' >= ch)
            h++;
        buf[bp++] = ch;
    }

    return 0;
}