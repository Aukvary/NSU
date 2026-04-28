#include <stdio.h>

int main() {
    long long n, m;
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    fscanf(in, "%lld %lld", &n, &m);

    long long sum = 0;
    for (long long i = 0; i < n; i++) {
        long long current;
        fscanf(in, "%lld", &current);
        
        sum = (sum + current) % m;
        if (sum < 0) {
            sum += m;
        }
    }

    fprintf(out, "%lld\n", sum);

    fclose(in);
    fclose(out);
    return 0;
}