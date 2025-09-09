#include <stdio.h>

int main(void) {
    int n;
    int m/*номер*/, p/*подъезд*/, k/*этаж*/, l/*кол-во этажей*/;

    scanf("%d", &n);
    scanf("%d %d %d %d", &m, &p, &k, &l);

    int c = 1;

    while (1) {
        int min = ((p - 1) * l + k - 1) * c + 1;
        int max = ((p - 1) * l + k - 1) * c + c;

        if (m >= min && m <= max)
            break;

        c++;
    }

    int a = (n - 1) / c;
    int i = a / l + 1;
    int j = a % l + 1;

    printf("%d %d", i, j);
}