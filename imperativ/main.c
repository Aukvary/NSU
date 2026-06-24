#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int size;
char** gnums;
int n;
int trim;
int* trims[101] = { 0 }; 
bool cond;

void counting_sort(int c, int* trimes, int* temp_trims) {
    int counts[10] = {0};

    for (int i = 0; i < n; i++) {
        int string_idx = trimes[i];
        counts[gnums[string_idx][c] - '0']++;
    }

    for (int i = 1; i < 10; i++) {
        counts[i] += counts[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int string_idx = trimes[i];
        int digit = gnums[string_idx][c] - '0';
        int idx = --counts[digit];
        temp_trims[idx] = string_idx;
    }
}

void radix_sort() {
    int* curr = malloc(sizeof(int) * n);
    int* temp = malloc(sizeof(int) * n);

    for (int j = 0; j < n; j++) {
        curr[j] = j;
    }

    for (int i = size - 1; i >= size - trim; i--) {
        counting_sort(i, curr, temp);
        for (int j = 0; j < n; j++) {
            curr[j] = temp[j];
        }
    }

    for (int j = 0; j < n; j++) {
        trims[trim][j] = curr[j];
    }

    free(curr);
    free(temp);
}

int* smallestTrimmedNumbers(
    char** nums, 
    int numsSize, 
    int** queries, 
    int queriesSize, 
    int* queriesColSize, 
    int* returnSize) {

        gnums = nums;
        n = numsSize;
        size = strlen(nums[0]);
        *returnSize = queriesSize;
        int* ans = malloc(sizeof(int) * queriesSize);
        cond = (size - 1) % 2;
        
        for (int i = 0; i < queriesSize; i++) {
            int k = queries[i][0];
            trim = queries[i][1];

            if (trims[trim] == NULL) {
                trims[trim] = malloc(sizeof(int) * n);
                radix_sort();
            }

            ans[i] = trims[trim][k - 1];
        }

        for (int i = 1; i <= size; i++) {
            if (trims[i] != NULL) {
                free(trims[i]);
                trims[i] = NULL;
            }
        }

        return ans;
}