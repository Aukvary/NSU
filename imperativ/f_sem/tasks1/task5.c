#include <stdio.h>
#include <math.h>

#define ABS(num) (num >= 0 ? num : -num)

int main(void) {
    float a, b;

    scanf("%f %f", &a, &b);

    printf("%d ", (int)floor(a / b));
    printf("%d ", (int)ceil(a / b));
    printf("%d ", (int)round(a / b));

    int c = (int)a % (int)b;
    printf("%d\n", c + (c < 0 ? (int)ABS(b) : 0)); 

    return 0;
}