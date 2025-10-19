#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t name[20];

    uint64_t size;

    uint8_t is_dir;

    uint64_t create_time;
    uint64_t update_time;

    uint8_t is_hidden;
} fileData;
#pragma pack(pop)

int filesCmp(const void* v1, const void* v2) {
    return strcmp(((const fileData*)v1)->name, ((const fileData*) v2)->name);
}


int main() {
    FILE* in = fopen("input.in", "rb");
    FILE* out = fopen("output.txt", "wb");

    uint32_t n;
    fread(&n, sizeof(uint32_t), 1, in);
    
    uint64_t a;
    uint64_t b;
    fread(&a, sizeof(uint64_t), 1, in);
    fread(&b, sizeof(uint64_t), 1, in);

    fileData* files = calloc(n, sizeof(fileData));

    fread(files, sizeof(fileData), n, in);

    uint64_t count = 0;

    for (int i = 0; i < n; i++) {
        if (files[i].create_time < a)               continue;
        if (files[i].update_time > b)               continue;
        if (files[i].is_dir || files[i].is_hidden)  continue;

        files[count++] = files[i];
    }

    qsort(files, count, sizeof(fileData), filesCmp);

    fwrite(files, sizeof(fileData), count, out);
    
    
    return 0;
}