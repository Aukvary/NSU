#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX 100001

uint32_t converte(uint32_t value) {
    return ((value >> 24) & 0x000000FF) |
           ((value >> 8)  & 0x0000FF00) |
           ((value << 8)  & 0x00FF0000) |
           ((value << 24) & 0xFF000000);
}

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    char need_swap = 0;

    uint32_t n;
    fread(&n, sizeof(uint32_t), 1, in);
    
    if (n > MAX) {
        n = converte(n);
        need_swap = 1;
    }

    uint32_t res = 0;
    
    for (int i = 0; i < n; i++) {
        uint32_t a;
        fread(&a, sizeof(uint32_t), 1, in);

        if (need_swap)
            a = converte(a);

        res += a;
    }

    if (need_swap)
        res = converte(res);

    fwrite(&res, sizeof(uint32_t), 1, out);

    return 0;
}