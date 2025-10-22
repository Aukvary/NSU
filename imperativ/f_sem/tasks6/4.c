#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint64_t code;
    uint32_t l;
} symb;

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");
    uint32_t n;

    fread(&n, sizeof(uint32_t), 1, in);

    symb* alf = malloc(n * sizeof(symb));
    uint32_t l;
    uint8_t byte;

    for (int i = 0; i < n; i++) {
        fread(&l, sizeof(uint32_t), 1, in);
        alf[i].l = l;
        alf[i].code = 0;
        for (int j = 0; j < l; j++) {
            fread(&byte, sizeof(uint8_t), 1, in);
            alf[i].code = alf[i].code << 1;
            alf[i].code += byte == 1;
        }
    }
    
    uint32_t m;
    fread(&m, sizeof(uint32_t), 1, in);
    
    uint8_t cur = 0;   
    int bit_count = 0;
    uint8_t* res = malloc(m * 8 + 8);
    int len = 0;
    
    for (int i = 0; i < m; i++) {
        uint16_t index;
        fread(&index, sizeof(uint16_t), 1, in);
        
        for (int j = alf[index].l - 1; j >= 0; j--) {
            uint8_t bit = (alf[index].code >> j) & 1;
            cur |= (bit << bit_count);
            bit_count++;
            
            if (bit_count == 8) {
                res[len++] = cur;
                cur = 0;
                bit_count = 0;
            }
        }
    }

    if (bit_count > 0) {
        res[len++] = cur;
    }

    fwrite(res, sizeof(uint8_t), len, out);

    return 0;
}