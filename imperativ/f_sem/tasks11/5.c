#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t A, B, M, R, S;

uint32_t hashFunc(uint32_t x) {
    return (((A * x + B) % M) % R) / S;
}

uint32_t xorshift32(uint32_t* state) {
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}

int main() {
    printf("start\n");

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);  
    
    scanf("%llu %llu %llu %llu %llu", &A, &B, &M, &R, &S);
    

    const int SAMPLES = 100000;
    int changes[32][32] = {0};
    
    uint32_t rng_state = 42;
    
    for (int k = 0; k < SAMPLES; k++) {
        uint32_t x = xorshift32(&rng_state);
        uint32_t h1 = hashFunc(x);
        
        for (int i = 0; i < 32; i++) {
            uint32_t x2 = x ^ (1u << i);
            uint32_t h2 = hashFunc(x2);
            
            uint32_t diff = h1 ^ h2;
            
            for (int j = 0; j < 32; j++) {
                if ((diff >> j) & 1) {
                    changes[i][j]++;
                }
            }
        }
    }
    
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            int percent = (changes[i][j] * 100 + SAMPLES / 2) / SAMPLES;
            if (j > 0) printf(" ");
            printf("%3d", percent);
        }
        printf("\n");
    }
    
    return 0;
}