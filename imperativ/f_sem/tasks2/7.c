#include <math.h>
#include <string.h>
#include <stdio.h>

#define TO_INT(c) ((c) - ((c) <= '9' ? '0' : ('a' - 10)))
#define TO_CHAR(n) ((char)((n) + ((n) < 10 ? '0' : ('a' - 10))))

int main() {
    char n[1000];
    int p, q;

    scanf("%d %d %s", &p, &q, n);
    int len = strlen(n) - 1;
    
    int temp = 0;
    for (int i = len; i >= 0; i--) {
        temp += ((int)pow(p, i)) * TO_INT(n[len - i]);
    }    

    char res[1000];
    len = 0;
    while (temp > 0) {
        res[len] = TO_CHAR(temp % q);
        temp /= q;
        len++;
    }

    for (len--; len > -1; len--) {
        printf("%c", res[len]);
    }
}