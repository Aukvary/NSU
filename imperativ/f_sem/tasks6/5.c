#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t name[21];
    uint64_t size;
    uint8_t is_dir;
    uint64_t create_time;
    uint64_t update_time;
    uint8_t is_hidden;
} fileData;
#pragma pack(pop)

int filesCmp(const void* v1, const void* v2) {
    const fileData* f1 = (const fileData*)v1;
    const fileData* f2 = (const fileData*)v2;
    return strcmp((const char*)f1->name, (const char*)f2->name);
}

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    uint32_t n;
    fread(&n, sizeof(uint32_t), 1, in);
    
    uint64_t a;
    uint64_t b;

    fread(&a, sizeof(uint64_t), 1, in);
    fread(&b, sizeof(uint64_t), 1, in);
    
    fileData* files = malloc(n * sizeof(fileData));

    size_t read_count = fread(files, sizeof(fileData), n, in);

    fileData* filtered = calloc(n, sizeof(fileData));
    uint32_t count = 0;

    for (int i = 0; i < n; i++) {
        if (files[i].is_dir || files[i].is_hidden) {
            continue;
        }
        
        if (files[i].create_time >= a && files[i].update_time <= b) {
            filtered[count++] = files[i];
        }
    }

    qsort(filtered, count, sizeof(fileData), filesCmp);

    fwrite(filtered, sizeof(fileData), count, out);
    
    return 0;
}