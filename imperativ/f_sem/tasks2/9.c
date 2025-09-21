#include <stdio.h>

int main() {
    char c;
    char prev;

    char com = 0;
    char block_com = 0;

    FILE* in = fopen("input.txt", "r");


    while (fscanf(in, "%c", &c) != -1) {
        
        if (block_com && prev == '*' && c == '/') {
            block_com = 0;
            prev = 0;
            continue;
        } else if (com && c == '\n') {
            com = 0;
            prev = c;
            continue;
        } else {
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
        
        if ((!block_com && !com) || prev == '\n' || prev == ' ' || prev == '\t')
            printf("%c", prev);

        prev = c;
    }

    if ((!block_com && !com) || prev == '\n' || prev == ' ' || prev == '\t')
        printf("%c", prev);

    return 0;
}