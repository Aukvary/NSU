#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void) {
    freopen("input.txt", "r", stdin);
    
    int t;
    int a;
    int b;
    
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d %d", &a, &b);
        
        printf("%d\n", gcd(a, b));
    }
    
    return 0;
}