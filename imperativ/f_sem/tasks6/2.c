#include <stdint.h>
#include <stdio.h>

#define UTF8_1BYTE_MASK  0x80
#define UTF8_2BYTE_MASK  0xE0
#define UTF8_3BYTE_MASK  0xF0
#define UTF8_4BYTE_MASK  0xF8

#define UTF8_1BYTE_VALUE 0x00
#define UTF8_2BYTE_VALUE 0xC0
#define UTF8_3BYTE_VALUE 0xE0
#define UTF8_4BYTE_VALUE 0xF0

#define UTF8_CONTINUATION_MASK 0xC0
#define UTF8_CONTINUATION_VALUE 0x80

#define UTF8_2BYTE_DATA_MASK1 0x1F
#define UTF8_2BYTE_DATA_MASK2 0x3F
#define UTF8_3BYTE_DATA_MASK1 0x0F
#define UTF8_3BYTE_DATA_MASK2 0x3F
#define UTF8_4BYTE_DATA_MASK1 0x07
#define UTF8_4BYTE_DATA_MASK2 0x3F

#define MIN_2BYTE_VALUE 0x80
#define MIN_3BYTE_VALUE 0x800
#define MIN_4BYTE_VALUE 0x10000

#define SURROGATE_START 0xD800
#define SURROGATE_END   0xDFFF

#define MAX_UNICODE_VALUE 0x10FFFF

#define REPLACEMENT_CHAR 0xFFFD

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");
    
    uint8_t byte1;
    uint32_t symb;
    int trable = 0;

    while (fread(&byte1, 1, 1, in) == 1 && !trable) {
        if ((byte1 & UTF8_1BYTE_MASK) == UTF8_1BYTE_VALUE) {
            symb = byte1;
        } else if ((byte1 & UTF8_2BYTE_MASK) == UTF8_2BYTE_VALUE) {
            uint8_t byte2;
            if (fread(&byte2, 1, 1, in) != 1) {
                trable = 1;
                break;
            }
            if ((byte2 & UTF8_CONTINUATION_MASK) != UTF8_CONTINUATION_VALUE) {
                trable = 1;
                break;
            }
            symb = ((byte1 & UTF8_2BYTE_DATA_MASK1) << 6) | (byte2 & UTF8_2BYTE_DATA_MASK2);
            if (symb < MIN_2BYTE_VALUE) {
                symb = REPLACEMENT_CHAR;
            }
        } else if ((byte1 & UTF8_3BYTE_MASK) == UTF8_3BYTE_VALUE) {
            uint8_t byte2;
            uint8_t byte3;
            if (fread(&byte2, 1, 1, in) != 1) {
                trable = 1;
                break;
            }
            if (fread(&byte3, 1, 1, in) != 1) {
                trable = 1;
                break;
            }
            if ((byte2 & UTF8_CONTINUATION_MASK) != UTF8_CONTINUATION_VALUE) {
                trable = 1;
                break;
            }
            if ((byte3 & UTF8_CONTINUATION_MASK) != UTF8_CONTINUATION_VALUE) {
                trable = 1;
                break;
            }
            
            symb = ((byte1 & UTF8_3BYTE_DATA_MASK1) << 12) | 
                   ((byte2 & UTF8_3BYTE_DATA_MASK2) << 6) | 
                   (byte3 & UTF8_3BYTE_DATA_MASK2);
            if (symb < MIN_3BYTE_VALUE) {
                symb = REPLACEMENT_CHAR;
            }
        } else if ((byte1 & UTF8_4BYTE_MASK) == UTF8_4BYTE_VALUE) {
            uint8_t byte2;
            uint8_t byte3;
            uint8_t byte4;
            if (fread(&byte2, 1, 1, in) != 1) {
                trable = 1;
                break;
            }
            if (fread(&byte3, 1, 1, in) != 1) {
                trable = 1;
                break;
            }
            if (fread(&byte4, 1, 1, in) != 1) {
                trable = 1;
                break;
            }
            if ((byte2 & UTF8_CONTINUATION_MASK) != UTF8_CONTINUATION_VALUE) {
                trable = 1;
                break;
            }
            if ((byte3 & UTF8_CONTINUATION_MASK) != UTF8_CONTINUATION_VALUE) {
                trable = 1;
                break;
            }
            if ((byte4 & UTF8_CONTINUATION_MASK) != UTF8_CONTINUATION_VALUE) {
                trable = 1;
                break;
            }
            
            symb = ((byte1 & UTF8_4BYTE_DATA_MASK1) << 18) | 
                   ((byte2 & UTF8_4BYTE_DATA_MASK2) << 12) | 
                   ((byte3 & UTF8_4BYTE_DATA_MASK2) << 6) | 
                   (byte4 & UTF8_4BYTE_DATA_MASK2);
            if (symb < MIN_4BYTE_VALUE) {
                symb = REPLACEMENT_CHAR;
            }
        } else {
            trable = 1;
            break;
        }
        
        if ((symb >= SURROGATE_START && symb <= SURROGATE_END) || symb > MAX_UNICODE_VALUE) {
            symb = REPLACEMENT_CHAR;
        }
        
        fwrite(&symb, 4, 1, out);    
    }


    return 0;
}