#include <stdio.h>

int main() {
    char s[1001];

    fgets(s, sizeof(s), fopen("input.txt", "r"));

    int n = 0;
    while (s[++n] != '\0');
    
    int l = 0;
    int r = 0;
    for (; r <= n; r++) {
        if (s[r] != ' ' && s[r] != '\0') 
            continue;
            
        if (l == r - 1 || s[l] == ' ' || s[l] == '\0') {
            printf("%c ", s[l]);
        } else {
            printf("%c%d%c ", s[l], r - l - 2, s[r - 1]);
        }
        
        l = r + 1;
    }

    return 0;
}
