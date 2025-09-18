#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    char c;
    int num;

    for (int i = 0; i < n; i++) {
        scanf("%c", &c);

        if (c != '1' && c != '0') {
            i--;
            continue;
        }
        
        if (c == '1')
            num += 1 << (i % 8);

        if (i % 8 == 7) {
            printf("%d ", num);
            num = 0;
        }
    }

    printf("%d", num);
}