#include <stdio.h>

int main() {
    int n;

    scanf("%d", &n);

    int buf[10000];

    for (int i = 0; i < n; i++) {
        scanf("%d", &buf[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        int count = 0;

        for (int j = i + 1; j < n; j++) {
            if (buf[i] > buf[j])
                count += 1;
        }
        printf("%d ", count);
    }

    printf("0");

    return 0;
}