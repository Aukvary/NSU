#include <stdio.h>

int main(void) {
    int x, y, z;

    scanf("%d %d %d", &x, &y, &z);

    if (x <= 0) {
        printf("%d", -1);
        return;
    } else if (y <= 0) {
        printf("%d", -2);
        return;
    } else if (z <= 0) {
        printf("%d", -3);
        return;
    }

    printf("%d\n", (x * y + x * z + y * z) * 2);
}