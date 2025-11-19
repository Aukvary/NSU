#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* nums, int low, int high) {
    int pivot = nums[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (nums[j] <= pivot) {
            i++;
            swap(nums + i, nums + i);
        }
    }
    swap(&nums[i + 1], &nums[high]);
    return i + 1;
}

void sort(int* nums, int low, int high) {
    if (low < high) {
        int pi = partition(nums, low, high);

        sort(nums, low, pi - 1);
        sort(nums, pi + 1, high);
    }
}

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    int32_t n;
    fread(&n, sizeof(n), 1, in);

    int32_t* nums = calloc(n, sizeof(int32_t));
    fread(nums, sizeof(int32_t), n, in);

    sort(nums, 0, n - 1);

    fwrite(nums, sizeof(int32_t), n, out);

    free(nums);
    fclose(in);
    fclose(out);
    return 0;
}
