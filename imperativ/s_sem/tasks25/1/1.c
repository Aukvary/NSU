#include <stdio.h>

static char buffer[65536];
static int pos = 0;
static int len = 0;

char get_char(FILE *in) {
    if (pos == len) {
        len = fread(buffer, 1, 65536, in);
        pos = 0;
        if (len == 0) return EOF;
    }
    return buffer[pos++];
}

long long read_ll(FILE *in) {
    long long res = 0;
    int sign = 1;
    char c = get_char(in);
    while (c != EOF && (c < '0' || c > '9') && c != '-') c = get_char(in);
    if (c == '-') {
        sign = -1;
        c = get_char(in);
    }
    while (c >= '0' && c <= '9') {
        res = res * 10 + (c - '0');
        c = get_char(in);
    }
    return res * sign;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    long long n = read_ll(in);
    long long x = read_ll(in);

    long long first_idx = -1;
    for (long long i = 0; i < n; i++) {
        long long current = read_ll(in);
        if (current == x) {
            first_idx = i;
            break;
        }
        if (current > x) break;
    }

    if (first_idx != -1) {
        printf("YES %lld\n", first_idx);
    } else {
        printf("NO\n");
    }

    fclose(in);
    return 0;
}