#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EMPTY 0x7FFFFFFF

int32_t* uniq_nums;
int32_t n;

int insert(int num) {    
    int key = num % n;
    if (key < 0) key += n;
    
    int start_key = key;
    
    while (uniq_nums[key] != EMPTY) {
        if (uniq_nums[key] == num) return 0;
        key = (key + 1) % n;
        if (key == start_key) return 0;
    }

    uniq_nums[key] = num;
    return 1;
}

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    fread(&n, sizeof(n), 1, in);

    int32_t* nums = calloc(n, sizeof(int32_t));
    int32_t* result = calloc(n, sizeof(int32_t));
    uniq_nums = calloc(n, sizeof(int32_t));

    for (int i = 0; i < n; i++) {
        uniq_nums[i] = EMPTY;
    }

    fread(nums, sizeof(int32_t), n, in);
    
    int result_count = 0;
    for (int i = 0; i < n; i++) {
        if (insert(nums[i])) {
            result[result_count++] = nums[i];
        }
    }
    fwrite(&result_count, sizeof(result_count), 1, out);
    fwrite(result, sizeof(int32_t), result_count, out);

    return 0;
}