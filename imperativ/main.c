#include <stdio.h>

int main() {
    const int a = 10;
    printf("%d\n", a);
    
    *((int*)&a) = 2;
    printf("%d\n", a);

    return 0;
}