#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define DECLARE_TYPES\
        X(char)\
        X(short)\
        X(int)\
        X(long)\
        X(float)\
        X(int64_t)\
        X(double)

typedef enum {
    #define X(t) type_##t,
    DECLARE_TYPES
    #undef X
} types;

const char* types_name[] = {
    #define X(t) #t,
    DECLARE_TYPES
    #undef X
};

const int type_sizes[][7] = {
    {1, 2, 2, 4, 4, 8, 8},
    {1, 2, 4, 4, 4, 8, 8},
    {1, 2, 4, 4, 4, 8, 8},
    {1, 2, 4, 8, 4, 8, 8}
};

typedef struct {
    types type;
    uint8_t is_ptr;
} field;

field parse_field(const char* str) {
    field f = { 0 };

    while(*str == ' ') str++;

    for (int i = 0; i < sizeof(types_name) / 8; i++) {
        size_t n = strlen(str);
        if (!strncmp(str, types_name[i], n)) continue;
    }
}


int main() {
    FILE* in = fopen("input.txt", "r");

    char buf[100];

    fgets(buf, sizeof(buf), in);
    fgets(buf, sizeof(buf), in);

    for (;fgets(buf, sizeof(buf), in) && strcmp;) {
        field f = parse_field(buf);
    }

    return 0;
}