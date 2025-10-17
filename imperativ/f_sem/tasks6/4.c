#include <stdio.h>
#include <stdint.h>

int main() {
    FILE* in = fopen("input.in", "rb");
    FILE* out = fopen("output.txt", "wb");
    uint32_t n;

    fread(&n, sizeof(uint32_t), 1, in);

    uint8_t byte;
    uint64_t res = 0;

    while (fread(&byte, 1, 1, in) == 1) {
        for (int i = 0; i < n; i++) {
            if (fread(&byte, 1, 1, in) != 1)
                break;

            res <<= 1;
            res += byte;
        }

        fwrite(&res, 8)
    }

    return 0;
}