#include <stdio.h>

#define SIZE 1000000

void split(FILE* in) {
    char s[SIZE] = { 0 };
    char ch = 0;
    int bp = 0;
    int h = 0;
    int c = 0;
    for (int i = 0; (ch = fgetc(in)) != EOF; i++) {
        if (ch == '.' || ch == ',' || ch == ':' || ch == ';' || ch == '\0' || ch == '\n') {
            if (c > 0)
                printf("%d/%d %s\n", h, c, s);

            for (int j = 0; j < bp; j++)
                s[j] = 0;
            h = 0;
            c = 0;
            bp = 0;
            continue;
        }
        c++;
        if (ch >= 'A' && 'Z' >= ch)
            h++;
        s[bp++] = ch;
    }
}

int main() {
    FILE* in = fopen("input.txt", "r");
    
    split(in);

    return 0;
}