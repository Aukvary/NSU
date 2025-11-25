#include <stdio.h>

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;
    long long k;
    fscanf(in, "%d %lld", &n, &k);

    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + k) % i;
    }

    printf("%d\n", result + 1);

    return 0;
}
