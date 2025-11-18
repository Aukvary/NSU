#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void sort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        sort(arr, low, pi - 1);
        sort(arr, pi + 1, high);
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