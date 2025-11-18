#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void swap(int32_t* a, int32_t* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void make_heap(int32_t* nums, int n, int i) {
    while (1) {
        int bigger = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && nums[left] > nums[bigger]) {
            bigger = left;
        }
        
        if (right < n && nums[right] > nums[bigger]) {
            bigger = right;
        }

        if (bigger == i) break;
        
        swap(nums + i, nums + bigger);
        i = bigger;
    }
}

void sort(int32_t* nums, int n) {
    for (int i = n / 2 - 1; i > -1; i--) {
        make_heap(nums, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(nums, nums + i);
        make_heap(nums, i, 0);
    }
}

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    uint32_t n;
    fread(&n, sizeof(n), 1, in);

    int32_t* nums = calloc(n, sizeof(int32_t));
    fread(nums, sizeof(int32_t), n, in);

    sort(nums, n);

    fwrite(nums, sizeof(int32_t), n, out);

    free(nums);
    fclose(in);
    fclose(out);
    return 0;
}