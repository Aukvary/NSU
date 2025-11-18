#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void sort(int32_t* nums, int len) {
    if (len < 2) return;
    
    int len_l = len / 2;
    int len_r = len - len_l;

    int32_t* nums_l = nums;
    int32_t* nums_r = nums + len_l;

    sort(nums_l, len_l);
    sort(nums_r, len_r);

    int32_t* temp = calloc(len, sizeof(int32_t));
    
    int i = 0, l_i = 0, r_i = 0;
    
    while (l_i < len_l && r_i < len_r) {
        if (nums_l[l_i] <= nums_r[r_i]) {
            temp[i++] = nums_l[l_i++];
        } else {
            temp[i++] = nums_r[r_i++];
        }
    }
    
    while (l_i < len_l) {
        temp[i++] = nums_l[l_i++];
    }
    while (r_i < len_r) {
        temp[i++] = nums_r[r_i++];
    }
    
    for (int i = 0; i < len; i++) {
        nums[i] = temp[i];
    }
    
    free(temp);
}

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    int32_t n;
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