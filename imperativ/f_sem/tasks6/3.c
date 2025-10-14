#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE* in = fopen("input.txt", "r");
    
    int n;
    fscanf(in, "%d", &n);
    
    for (int i = 0; i < n; i++) {
        int p, q;
        unsigned long long m;
        fscanf(in, "%d/%d xor %llx", &p, &q, &m);
        
        double x = (double)p / q;
        unsigned long long bits;
        memcpy(&bits, &x, 8);
        bits ^= m;
        double result;
        memcpy(&result, &bits, 8);
        
        printf("%.15g\n", result);
    }
    
    return 0;
}