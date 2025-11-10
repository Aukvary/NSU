#include <stdlib.h>
#include <stdio.h>

#define SIZE 100000

typedef enum {
    SORT,
    PRINT,
    SEARCH,
    XOR
} commands;

void sort(int* nums, int n) {
    int buckets[SIZE] = { 0 };
    for (int i = 0; i < n; i++) {
        buckets[nums[i]] += 1;
    } 

    int a = 0;

    for (int i = 0; i < n; i++) {
        while(!buckets[a])
            a++;
        nums[i] = a;
        buckets[a]--;
    }
}

int bin_search(int* nums, int n, int target) {
    int l = 0;
    int r = n - 1;

    int i = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (nums[m] == target) {
            i = m;
            break;
        } else if (nums[m] < target) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    if (i == -1) return -1;
    if (i == 0) return i;

    while (nums[i] == target) i--;

    return i + 1;
}


int search(int* nums, int n, int target, char sorted) {
    if (sorted) return bin_search(nums, n, target);

    for (int i = 0; i < n; i++) {
        if (nums[i] == target) return i;
    }

    return -1;
}

void print(int* nums, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", nums[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
}

commands parse_command(const char* str) {
    return str[0] == 'p' ? PRINT :
        (str[0] == 'X' ? XOR : 
            (str[1] == 'o' ? SORT : SEARCH));
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int sorted = 0;

    int nums1[SIZE];
    int nums2[SIZE];

    int n = 0;

    while (1) {
        int  buf;
        fscanf(in, "%d", &buf);
        if (buf == -1) break;
        nums1[n] = buf;
        n++;
    }

    for (int i = 0; i < n; i++) {
        int  buf;
        fscanf(in, "%d", &buf);
        nums2[i] = buf;
    }

    char buf[20];
    while (fscanf(in, "%s", buf) != EOF) {
        commands cmd = parse_command(buf);

        switch (cmd) {
            case PRINT: {
                print(nums1, n);
                print(nums2, n);
                break;
            } case SORT: {
                sort(nums1, n);
                sort(nums2, n);

                sorted = 1;

                break;
            } case SEARCH: {
                int target;
                fscanf(in, "%d", &target);
                int idx = 0;
                if ((idx = search(nums1, n, target, sorted)) != -1) {
                    printf("%d %d\n", 1, idx + 1);
                    break;
                }
                idx = search(nums2, n, target, sorted);
                if (idx == -1) {
                    printf("-1\n");
                    break;
                }

                printf("%d %d\n", 2, idx + 1);

                break;
            } case XOR: {
                int res = 0;
                for (int i = 0; i < n; i++) {
                    res += nums1[i] ^ nums2[i];
                }
                printf("%d\n", res);
                break;
            }
        }
    }

    return 0;
}