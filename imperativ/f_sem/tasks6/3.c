#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE* in = fopen("input.txt", "r");
    
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        int p, q;
        unsigned long long m;
        scanf( "%d/%d xor %llx", &p, &q, &m);
        
        double x = (double)p / q;
        unsigned long long bits = *(unsigned long long *)&x;
        bits ^= m;  
        double result = *(double *)&bits;
        
        printf("%.15g\n", result);
    }
    
    return 0;
}