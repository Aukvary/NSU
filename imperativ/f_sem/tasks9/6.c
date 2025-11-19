#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint32_t key;
    uint32_t value;
} KeyValuePair;

uint32_t get_byte(uint32_t num, int i) {
    return (num >> (8 * i)) & 0xFF;
}

void counting_sort(KeyValuePair* nums, int n, int byte) {
    uint32_t bytes[256] = { 0 };
    KeyValuePair* res = calloc(n, sizeof(KeyValuePair));

    for (int i = 0; i < n; i++) {
        bytes[get_byte(nums[i].key, byte)] += 1;
    }

    for (int i = 1; i < 256; i++) {
        bytes[i] += bytes[i - 1];
    }

    for (int i = n - 1;  i > -1; i--) {
        res[--bytes[get_byte(nums[i].key, byte)]] = nums[i];
    }

    memcpy(nums, res, n * sizeof(KeyValuePair));

    free(res);
}

void sort(KeyValuePair* nums, int n) {
    for (int i = 0; i < 4; i++) {
        counting_sort(nums, n, i);
    }
}

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    uint32_t n;
    fread(&n, sizeof(n), 1, in);

    KeyValuePair* nums = calloc(n, sizeof(KeyValuePair));
    fread(nums, sizeof(KeyValuePair), n, in);

    sort(nums, n);

    fwrite(nums, sizeof(KeyValuePair), n, out);

    free(nums);
    return 0;
}