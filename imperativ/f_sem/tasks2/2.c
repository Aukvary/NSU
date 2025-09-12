#include <math.h>
#include <stdio.h>

typedef union color {
    int hex;
    struct {
        unsigned char b;
        unsigned char g;
        unsigned char r;
    };
} color;

int main() {
    char input[6];
    scanf("%6s", &input);

    color col = { 0 };

    for (int i = 0; i < 6; i++) {
        char digit = input[i] >= '0' && input[i] <= '9';
        char symb_digit = input[i] >= 'A' && input[i] <= 'F';
        char small_symb_digit = input[i] >= 'a' && input[i] <= 'f';

        int value;

        if (!digit && !symb_digit && !small_symb_digit) {
            printf("-1 -1 -1");
            return 0;
        }
        
        if (digit) value = input[i] - '0';    
        else if (symb_digit) value = input[i] - 'A' + 10;
        else value = input[i] - 'a' + 10;

        col.hex += (int)pow(16, 5 - i) * value;
    }

    printf("%hhu %hhu %hhu", col.r, col.g, col.b);

    return 0;
}