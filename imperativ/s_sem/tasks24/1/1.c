#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    int candidate = 0;
    int count = 0;
    int *arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (count == 0) {
            candidate = arr[i];
            count = 1;
        } else if (arr[i] == candidate) {
            count++;
        } else {
            count--;
        }
    }

    int actual_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == candidate) {
            actual_count++;
        }
    }

    if (actual_count > n / 2) {
        printf("YES %d\n", candidate);
    } else {
        printf("NO\n");
    }

    free(arr);
    return 0;
}