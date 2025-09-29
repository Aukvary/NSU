#include <stdio.h>

int main() {
    char str[1001] = { 0 };
    fgets(str, sizeof(str), fopen("input.txt", "r"));

    char* s = str;

    while (*s) {
        while (*s == ' ')
            s++;
        
        if (!(*s)) 
            break;

        int len = 0;

        while (*(s + 1) != ' ' && *(s + 1) != '\0') {
            s++;
            len++;
        }

        if (len == 0){
            printf("%c ", *s);
            s++;
        } else {
            printf("%c%d%c ", *(s - len), len - 1, *s);
            s++;
        }
    }

    return 0;
}
