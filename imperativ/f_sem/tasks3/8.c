#include <stdio.h>

int main() {
    int n;
    int sizes[100000];

    FILE* in = fopen("input.txt", "r");

    fscanf(in, "%d", &n);

    for (int i = 0; i < n; i++)
        fscanf(in, "%d", &sizes[i]);


    int l = 0;
    int r = n - 1;
    int l_m = 0;
    int r_m = 0;
    int count = 0;

    while (l < r) {
        if (sizes[l] < sizes[r]) {
            if (sizes[l] >= l_m) {
                l_m = sizes[l];
            } else {
                count += l_m - sizes[l];
            }
            l++;
        } else {
            if (sizes[r] >= r_m) {
                r_m = sizes[r];
            } else {
                count += r_m - sizes[r];
            }
            r--;
        }
    }
    
    printf("%d", count);

    return 0;
}