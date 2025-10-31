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
    {4, 4, 8, 8}
};

types parse_field(const char* str) {
    while(*str == ' ') str++;
    if (strchr(str, '*')) return type_ptr;

    for (int i = (sizeof(types_name) / sizeof(types_name[0])) - 2; i > -1; i--) {
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
        if (padding < size) padding = size;
        while (res % size) res++;
        res += size;
    }

    while (res % padding) res++;

    return res;
}

int get_max(int n, int mode) {
    int res = 0;
    int padding = 1;

    int l = 0;
    int r = n - 1;

    char big = 0;

    while (l <= r) {
        int size;
        if (big) {
            size = types_size[fields[r]][mode];
            r--;
        } else {
            size = types_size[fields[l]][mode];
            l++;
        }
        big = !big;

        if (padding < size) padding = size;
        while (res % size) res++;
        res += size;
    }

    while (res % padding) res++;

    return res;
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
        printf("%d %d\n", get_min(n, i), get_max(n, i));
    }

    // printf("8 12\n12 12\n16 24\n16 24\n");

    return 0;
}