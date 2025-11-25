#include <stdio.h>

int main() {
    int n;

    scanf("%d", &n);

    int buf[10000];

    for (int i = 0; i < n; i++) {
        scanf("%d", &buf[i]);
    }

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j += (i + 1)) {
            sum += buf[j];
        }

        printf("%d\n", sum);
    }

    return 0;
}
