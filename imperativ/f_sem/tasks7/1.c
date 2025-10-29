#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DECLARE_TYPES\
        X(char)\
        X(short)\
        X(int)\
        X(long)\
        X(float)\
        X(int64_t)\
        X(double)\
        X(ptr)

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

const int types_size[][4] = {
    {1, 1, 1, 1},
    {2, 2, 2, 2},
    {2, 4, 4, 4},
    {4, 4, 4, 8},
    {4, 4, 4, 4},
    {8, 8, 8, 8},
    {8, 8, 8, 8},
    {2, 4, 8, 8}
};

types parse_field(const char* str) {
    while(*str == ' ') str++;
    if (strchr(str, '*')) return type_ptr;

    for (int i = (sizeof(types_name) / sizeof(types_name[0])) - 1; i > -1; i--) {
        size_t len = strlen(types_name[i]);
        
        if (strncmp(str, types_name[i], len) != 0)
            continue; 

        return i;
    }
}

types fields[100000] = { 0 };

void insert_sort(types* fields, int len, int mode) {
    for (int i = 1; i < len; i++) {
        for (int j = i; j > 0 && types_size[fields[j - 1]][mode] > types_size[fields[j]][mode]; j--) {
            types temp = fields[j - 1];
            fields[j - 1]= fields[j];
            fields[j] = temp;
        }
    }
}

int get_min(int n, int mode) {
    int res = 0;
    int padding = 1;

    for (int i = n - 1; i > -1; i--) {
        int size = types_size[fields[i]][mode];
        while (res % size) res++;
        if (padding < size) padding = size;
        res += size;
    }

    while (res % padding) res++;

    return res < 8 ? 8 : res;
}

int main() {
    FILE* in = fopen("input.txt", "r");

    char buf[100];
    fgets(buf, sizeof(buf), in);
    fgets(buf, sizeof(buf), in);

    int n;
    while(fgets(buf, sizeof(buf), in)[0] != '}') {
        fields[n++] = parse_field(buf);
    }

    for (int i = 0; i < 4; i++) {
        insert_sort(fields, n, i);
        printf("%d\n", get_min(n, i));
    }

    return 0;
}