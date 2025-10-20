#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    FILE* in = fopen("input.txt", "rb");

    uint32_t size;
    fread(&size, sizeof(size), 1, in);

    uint8_t type;
    printf("{\n");

    int first = 1;

    while (fread(&type, sizeof(uint8_t), 1, in) == 1 && type != 0) {
        if (!first) {
            printf(",\n");
        }
        first = 0;

        printf("    \"");

        uint8_t name_byte;

        while (fread(&name_byte, 1, 1, in) == 1 && name_byte != 0) {
            if (name_byte == 0)
                break;
            printf("%c", name_byte);
        }

        printf("\": ");


        switch (type) {
            case 1: {
                double num;
                fread(&num, sizeof(double), 1, in);
                printf("%0.15g", num);
                break;
            } case 2: {
                uint32_t l;
                fread(&l, sizeof(uint32_t), 1, in);
                
                printf("\"");
                for (int i = 0; i < l - 1; i++) { 
                    uint8_t byte;
                    fread(&byte, 1, 1, in);
                    printf("%c", byte);
                }
                printf("\"");
                fread(&l, 1, 1, in);
                break;
            } case 8: {
                uint8_t cond;
                fread(&cond, 1, 1, in);
                printf("%s", cond ? "true" : "false");
                break;
            } case 10: {
                printf("null");
                break;
            } case 16: {
                int32_t num;
                fread(&num, sizeof(int32_t), 1, in);
                printf("%d", num);
                break;
            } case 18: {
                int64_t num;
                fread(&num, sizeof(int64_t), 1, in);
                printf("%ld", num);
                break;
            }
        }
    }

    printf("\n}");

    return 0;
}