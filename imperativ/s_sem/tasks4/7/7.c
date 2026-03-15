#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t u32;

#ifdef BINARY_IO
#define SCAN(f, x) fread(&(x), sizeof(u32), 1, f)
#define PRINT(f, x) fwrite(&(x), sizeof(u32), 1, f)
#else
#define SCAN(f, x) fscanf(f, "%u", &(x))
#define PRINT(f, x) fprintf(f, "%u\n", x)
#endif

void func() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    u32* a = malloc(1000000 * sizeof(u32));

    u32 n = 0;
    u32 capacity = 1000000;  

    while (SCAN(in, a[n]) == 1) {
        n++;
        if (n == capacity) {
            capacity *= 2;
            a = realloc(a, capacity * sizeof(u32));
        }
    }
    fclose(in);

    if (n < 2) {
        PRINT(out, n);
        if (n > 0) PRINT(out, 0);
        if (n > 1) PRINT(out, 1);
        for (u32 i = 0; i < n; i++) PRINT(out, a[i]);
        fclose(out);
        free(a);
        return;
    }

    u32 len = 2;
    u32 l = 0;
    u32 r = 1;

    u32 cur_len = 2;
    u32 cur_l = 0;
    u32 d = a[1] - a[0];

    for (u32 i = 2; i < n; i++) {
        if (a[i] - a[i-1] == d) {
            cur_len++;
        } else {
            cur_l = i-1;
            cur_len = 2;
            d = a[i] - a[i-1];
        }
        
        if (cur_len > len || (cur_len == len && cur_l < l)) {
            len = cur_len;
            l = cur_l;
            r = i;
        }
    }

    PRINT(out, len);
    PRINT(out, l);
    PRINT(out, r + 1);
    for (u32 i = l; i <= r; i++) {
        PRINT(out, a[i]);
    }

    fclose(out);
    free(a);
}

#ifdef NO_MAIN
void DoAll() {
    func();
}
#else
int main() {
    func();
    return 0;
}
#endif