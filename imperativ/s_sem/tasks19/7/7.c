#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXN 2000
#define CHUNK_SIZE 64

typedef uint64_t chunk;

chunk matrix[MAXN][(MAXN / CHUNK_SIZE) + 1];

int main() {
    int n;
    freopen("input.txt", "r", stdin);

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char row[MAXN + 1];
        scanf("%s", row);
        for (int j = 0; j < n; j++) {
            if (row[j] == '1' || i == j) {
                matrix[i][j / CHUNK_SIZE] |= ((chunk)1 << (j % CHUNK_SIZE));
            }
        }
    }

    int words_count = (n + CHUNK_SIZE - 1) / CHUNK_SIZE;

    for (int k = 0; k < n; k++) {
        int k_word_idx = k / CHUNK_SIZE;
        chunk k_bit = (chunk)1 << (k % CHUNK_SIZE);

        for (int i = 0; i < n; i++) {
            if (!(matrix[i][k_word_idx] & k_bit)) continue;

            for (int w = 0; w < words_count; w++) {
                matrix[i][w] |= matrix[k][w];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j / CHUNK_SIZE] & ((chunk)1 << (j % CHUNK_SIZE))) {
                fputc('1', stdout);
            } else {
                fputc('0', stdout);
            }
        }
        fputc('\n', stdout);
    }

    return 0;
}