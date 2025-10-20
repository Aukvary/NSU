#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define CHUNK_SIZE 8

typedef uint8_t bitword;

void bitsetZero(bitword* arr, int num) {
    memset(arr, 0, (num + CHUNK_SIZE - 1) / CHUNK_SIZE);
}

int bitsetGet(const bitword* arr, int idx) {
    return arr[idx / CHUNK_SIZE] >> (idx % CHUNK_SIZE) & 1;
}

void bitsetSet(bitword* arr, int idx, int newval) {
    if (newval) arr[idx / CHUNK_SIZE] = arr[idx / CHUNK_SIZE] | 1 << idx % CHUNK_SIZE;
    else        arr[idx / CHUNK_SIZE] = arr[idx / CHUNK_SIZE] & ~(1 << idx % CHUNK_SIZE);
}

int bitsetAny(const bitword* arr, int left, int right) {
    if (left >= right) return 0;
    
    int start_chunk = left / CHUNK_SIZE;
    int end_chunk = (right - 1) / CHUNK_SIZE;
    
    if (start_chunk == end_chunk) {
        uint8_t mask = ((1 << (right - left)) - 1) << (left % CHUNK_SIZE);
        return (arr[start_chunk] & mask) != 0;
    }
    
    uint8_t left_mask = 0xFF << (left % CHUNK_SIZE);
    if (arr[start_chunk] & left_mask) return 1;
    
    for (int i = start_chunk + 1; i < end_chunk; i++) {
        if (arr[i] != 0) return 1;
    }
    
    uint8_t right_mask;
    if (right % CHUNK_SIZE == 0) {
        right_mask = 0xFF;
    } else {
        right_mask = (1 << (right % CHUNK_SIZE)) - 1;
    }
    
    if (arr[end_chunk] & right_mask) return 1;
    
    return 0;
}

void bitsetSetSeg(bitword* arr, int left, int right, int newval) {
    int start_chunk = left / CHUNK_SIZE;
    int end_chunk = (right - 1) / CHUNK_SIZE;
    
    if (start_chunk == end_chunk) {
        uint8_t mask = ((1 << (right - left)) - 1) << (left % 8);
        if (newval) 
            arr[start_chunk] |= mask;
        else 
            arr[start_chunk] &= ~mask;
        return;
    }

    uint8_t left_mask = 0xFF << (left % 8);
    if (newval)
        arr[start_chunk] |= left_mask;
    else
        arr[start_chunk] &= ~left_mask;
    
    for (int i = start_chunk + 1; i < end_chunk; i++) {
        arr[i] = newval ? 0xFF : 0x00;
    }
    
    uint8_t right_mask;
    if (right % CHUNK_SIZE == 0) {
        right_mask = 0xFF;
    } else {
        right_mask = (1 << (right % CHUNK_SIZE)) - 1;
    }
    
    if (newval)
        arr[end_chunk] |= right_mask;
    else
        arr[end_chunk] &= ~right_mask;
}

int bitsetCount(const bitword* arr, int left, int right) {
    int count = 0;
    for (int i = left; i < right; i++) {
        count += (arr[i / CHUNK_SIZE] >> (i % CHUNK_SIZE)) & 1;
    }
    return count;
}

int main() {
    FILE* in = fopen("input.txt", "r");
    
    int n;
    fscanf(in, "%d", &n);
    
    bitword* arr = NULL;
    int size = 0;
    
    for (int i = 0; i < n; i++) {
        int t;
        fscanf(in, "%d", &t);
        
        if (t == 0) {
            int num;
            fscanf(in, "%d", &num);
            
            int bytes_needed = (num + CHUNK_SIZE - 1) / CHUNK_SIZE;
            if (arr) free(arr);
            arr = malloc(bytes_needed);
            size = num;
            
            bitsetZero(arr, num);
        } else if (t == 1) { 
            int idx;
            fscanf(in, "%d", &idx);
            printf("%d\n", bitsetGet(arr, idx));
        } else if (t == 2) {
            int idx, newval;
            fscanf(in, "%d%d", &idx, &newval);
            bitsetSet(arr, idx, newval);
        } else if (t == 3) {
            int left, right;
            fscanf(in, "%d%d", &left, &right);
            int result = bitsetAny(arr, left, right);
            printf("%s\n", result ? "some" : "none");
        } else if (t == 4) { 
            int left, right;
            fscanf(in, "%d%d", &left, &right);
            printf("%d\n", bitsetCount(arr, left, right));
        }
    }
    
    return 0;
}