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

typedef struct {
    types type;
    uint8_t is_ptr;
} field;

field parse_field(const char* str) {
    field f = { .type = -1, .is_ptr = 0 };

    while(*str == ' ') str++;

    for (int i = 0; i < (sizeof(types_name) / sizeof(types_name[0])); i++) {
        size_t len = strlen(types_name[i]);
        
        if (strncmp(str, types_name[i], len) != 0)
            continue; 

        f.type = i;
        str += len;

        while (*str != ';' && *str != '\0' && *str != '\n') {
            if (*str == '*') {
                f.is_ptr = 1;
                break;
            }
            str++;
        }
        break;
    }

    return f;
}

int main() {
    FILE* in = fopen("input.txt", "r");

    char buf[100];
    fgets(buf, sizeof(buf), in);
    fgets(buf, sizeof(buf), in);
    fgets(buf, sizeof(buf), in);

    printf("%s", types_name[parse_field(buf).type]);

    return 0;
}