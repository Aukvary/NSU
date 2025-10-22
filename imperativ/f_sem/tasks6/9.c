#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define CHUNK_SIZE 64
typedef uint64_t bitword;

uint8_t one_count[256] = {
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

void bitsetZero(bitword* arr, int num) {
    memset(arr, 0, ((num + CHUNK_SIZE - 1) / CHUNK_SIZE) * sizeof(bitword));
}

int bitsetGet(const bitword* arr, int idx) {
    return (arr[idx / CHUNK_SIZE] >> (idx % CHUNK_SIZE)) & 1;
}

void bitsetSet(bitword* arr, int idx, int newval) {
    if (newval) 
        arr[idx / CHUNK_SIZE] |= (1ULL << (idx % CHUNK_SIZE));
    else 
        arr[idx / CHUNK_SIZE] &= ~(1ULL << (idx % CHUNK_SIZE));
}

int bitsetAny(const bitword* arr, int left, int right) {
    if (left >= right) return 0;
    
    int l = left / CHUNK_SIZE;
    int r = (right - 1) / CHUNK_SIZE;
    
    if (l == r) {
        uint64_t mask = ((1ULL << (right - left)) - 1) << (left % CHUNK_SIZE);
        return (arr[l] & mask) != 0;
    }
    
    uint64_t mask_l = ~((1ULL << (left % CHUNK_SIZE)) - 1);
    if (arr[l] & mask_l) return 1;
    
    for (int i = l + 1; i < r; i++) {
        if (arr[i]) return 1;
    }
    
    int right_bits = right % CHUNK_SIZE;
    uint64_t mask_r = (right_bits == 0) ? ~0ULL : ((1ULL << right_bits) - 1);
    if (arr[r] & mask_r) return 1;
    
    return 0;
}

void bitsetSetSeg(bitword* arr, int left, int right, int newval) {
    if (left >= right) return;
    
    int l = left / CHUNK_SIZE;
    int r = (right - 1) / CHUNK_SIZE;
    
    if (l == r) {
        uint64_t mask = ((1ULL << (right - left)) - 1) << (left % CHUNK_SIZE);
        if (newval)
            arr[l] |= mask;
        else
            arr[l] &= ~mask;
        return;
    }
    
    uint64_t mask_l = ~((1ULL << (left % CHUNK_SIZE)) - 1);
    if (newval)
        arr[l] |= mask_l;
    else
        arr[l] &= ~mask_l;
    
    for (int i = l + 1; i < r; i++) {
        arr[i] = newval ? ~0ULL : 0ULL;
    }
    
    int right_bits = right % CHUNK_SIZE;
    uint64_t mask_r = (right_bits == 0) ? ~0ULL : ((1ULL << right_bits) - 1);
    if (newval)
        arr[r] |= mask_r;
    else
        arr[r] &= ~mask_r;
}

int bitsetCount(const bitword* arr, int left, int right) {
    int count = 0;
    int l = left / CHUNK_SIZE;
    int r = (right - 1) / CHUNK_SIZE;
    
    if (l == r) {
        for (int i = left; i < right; i++) {
            count += (arr[i / CHUNK_SIZE] >> (i % CHUNK_SIZE)) & 1;
        }
        return count;
    }
    
    for (int i = left; i < (l + 1) * CHUNK_SIZE; i++) {
        count += (arr[i / CHUNK_SIZE] >> (i % CHUNK_SIZE)) & 1;
    }
    
    for (int i = l + 1; i < r; i++) {
        uint64_t chunk = arr[i];
        for (int j = 0; j < 8; j++) {
            count += one_count[chunk & 0xFF];
            chunk >>= 8;
        }
    }
    
    for (int i = r * CHUNK_SIZE; i < right; i++) {
        count += (arr[i / CHUNK_SIZE] >> (i % CHUNK_SIZE)) & 1;
    }
    
    return count;
}

int main() {
    FILE* in = fopen("input.txt", "r");
    
    int n;
    fscanf(in, "%d", &n);
    
    bitword* arr = NULL;
    
    for (int i = 0; i < n; i++) {
        int t;
        fscanf(in, "%d", &t);
        
        if (t == 0) {
            int num;
            fscanf(in, "%d", &num);
            
            int chunks = (num + CHUNK_SIZE - 1) / CHUNK_SIZE;
            if (arr) free(arr);
            arr = malloc(chunks * sizeof(bitword));
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
            int left, right, newval;
            fscanf(in, "%d%d%d", &left, &right, &newval);
            bitsetSetSeg(arr, left, right, newval);
        } else if (t == 4) { 
            int left, right;
            fscanf(in, "%d%d", &left, &right);
            printf("%d\n", bitsetCount(arr, left, right));
        } else if (t == 5) {
            int left, right;
            fscanf(in, "%d%d", &left, &right);
            printf("%s\n", bitsetAny(arr, left, right) ? "some" : "none");
        }
    }
    
    if (arr) free(arr);
    fclose(in);
    return 0;
}