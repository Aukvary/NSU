#include <stdio.h>

int main() {
    char s[1001];

    fgets(s, sizeof(s), stdin);

    int n = 0;
    while (s[++n] != '\0');

    s[n] = ' ';
    
    int l = 0;
    int r = 0;
    for (; r < n; r++) {
        if (s[r + 1] != ' ') 
            continue;
            
        if (l == r) {
            printf("%c ", s[l]);
        } else {
            printf("%c%d%c ", s[l], r - l - 1, s[r]);
        }
        
        l = r + 1;
    }

    return 0;
}
