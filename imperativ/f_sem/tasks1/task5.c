#include <stdio.h>

int main(void) {
    float a, b;

    scanf("%f %f", &a, &b);

    printf("%d ", (int)floor(a / b));
    printf("%d ", (int)ceil(a / b));
    printf("%d ", (int)round(a / b));

    printf("%d\n", ((int)a % (int)b) + (a < 0 ? (int)b : 0)); 

    return 0;
}