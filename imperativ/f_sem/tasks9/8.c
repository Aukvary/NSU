#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert_sort(int* nums, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && nums[j] < nums[j - 1]; j--) {
            swap(nums + j, nums + j - 1);
        }
    }
}

int median_of_three(int* nums, int low, int high) {
    int mid = low + (high - low) / 2;
    
    if (nums[low] > nums[mid])
        swap(&nums[low], &nums[mid]);
    if (nums[low] > nums[high])
        swap(&nums[low], &nums[high]);
    if (nums[mid] > nums[high])
        swap(&nums[mid], &nums[high]);
    
    return mid;
}

int partition(int* nums, int low, int high) {
    int pivot_index = median_of_three(nums, low, high);
    int pivot = nums[pivot_index];
    
    swap(&nums[pivot_index], &nums[high]);
    
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (nums[j] <= pivot) {
            i++;
            swap(&nums[i], &nums[j]);
        }
    }
    
    swap(&nums[i + 1], &nums[high]);
    return i + 1;
}

void make_heap(int* nums, int n, int i) {
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

void heap_sort(int* nums, int n) {
    for (int i = n / 2 - 1; i > -1; i--) {
        make_heap(nums, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(nums, nums + i);
        make_heap(nums, i, 0);
    }
}

void sort(int* nums, int low, int high, int depth, int max_depth, int k) {
    int size = high - low + 1;
    
    if (size <= k) {
        insert_sort(nums + low, size);
        return;
    }
    
    if (depth > max_depth) {
        heap_sort(nums + low, size);
        return;
    }
    
    int pi = partition(nums, low, high);
    sort(nums, low, pi - 1, depth + 1, max_depth, k);
    sort(nums, pi + 1, high, depth + 1, max_depth, k);
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;

    fscanf(in, "%d", &n);

    int* nums = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", nums + i);
    }

    int k = 64;
    int max_depth = 2 * (int)log2f((float)n);
    sort(nums, 0, n - 1, 0, max_depth, k);

    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
    }

    free(nums);
}