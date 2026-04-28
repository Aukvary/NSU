#include <stdio.h>

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    long long n, x;
    fscanf(in, "%lld %lld", &n, &x);

    long long count = 0;
    long long first_pos = -1;

    for (long long i = 0; i < n; i++) {
        long long current;
        fscanf(in, "%lld", &current);
        if (current == x) {
            if (count == 0) {
                first_pos = ftell(in); 
            }
            count++;
        } else if (current > x) {
            break;
        }
    }

    if (count == 0) {
        fprintf(out, "NO");
    } else {
        fprintf(out, "%lld\n", count);
        
        fseek(in, 0, SEEK_SET);
        fscanf(in, "%lld %lld", &n, &x);
        
        int first_printed = 0;
        for (long long i = 0; i < n; i++) {
            long long current;
            fscanf(in, "%lld", &current);
            if (current == x) {
                if (first_printed) fprintf(out, " ");
                fprintf(out, "%lld", i);
                first_printed = 1;
            } else if (current > x) {
                break;
            }
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}