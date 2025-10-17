#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    FILE* in = fopen("input.txt", "r");

    uint32_t n;

    fscanf(in, "%d", &n);

    uint64_t* nums = calloc(n, sizeof(uint64_t));

    for (int i = 0; i < n; i++) {
        fscanf(in, "%llx", &nums[i]);
    }

    uint32_t res = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((nums[i] & nums[j]) == 0)
                res++;
        }
    }

    printf("%d", res);


    return 0;
}