#include <stdio.h>

int main(void) {
    int h, m, s, k;

    scanf("%d %d %d %d", &h, &m, &s, &k);

    s += k;
    m += s / 60;
    s %= 60;
    h += m / 60;
    m %= 60;
    h %= 24;

    printf("%d %d %d", h, m, s);
}