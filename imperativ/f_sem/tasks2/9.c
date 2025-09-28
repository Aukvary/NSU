#include <stdio.h>

int main() {
    freopen("output.txt", "w", stdout);
    char c;
    char prev;

    char com = 0;
    char block_com = 0;

    FILE* in = fopen("input.txt", "r");

    int init = 1;

    while (fscanf(in, "%c", &c) != -1) {
      
        if (block_com && prev == '*' && c == '/') {
            block_com = 0;
            prev = 0;
            init = 1;
            continue;
        } else if (com && c == '\n') {
            com = 0;
            prev = c;
            continue;
        } else if (!com && !block_com) {
            if (prev == '/' && c == '/') {
                com = 1;
                prev = 0;
                continue;
            } else if (prev == '/' && c == '*') {
                block_com = 1;
                prev = 0;
                continue;
            }
        }

        if ( init == 1 ) {
            init = 0;
        } else if ((!block_com && !com) || prev == '\n')
            printf("%c", prev);

        prev = c;
    }

    if ((!block_com && !com) || prev == '\n')
        printf("%c", prev);

    return 0;
}