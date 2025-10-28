#include <stdio.h>

typedef struct Tokens_s {
    int num; 
    char **arr; 
} Tokens;

void tokensSplit(Tokens *tokens, const char *str, const char *delims) {

    int n;
    while (*str) {
        while (strchr("aeiou", *str) != NULL)
    }

}

void tokensFree(Tokens *tokens) {
}

int main() {


    return 0;
}