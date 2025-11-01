#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;
    fscanf(in, "%d", &n);

    char** strs = calloc(n, sizeof(char*));
    int len = 0;
    for (int i = 0; i < n; i++) {
        int mode;
        fscanf(in, "%d", &mode);

        if (mode == 0) {
            //malloc
            int l;
            char* buf;
            fscanf(in, "%d", &l);
            buf = malloc(l + 1);
            fscanf(in, "%s", buf);

            strs[len++] = buf;
        } else if (mode == 1) {
            //free
            int idx;
            fscanf(in, "%d", &idx);
            free(strs[idx]);
        } else if (mode == 2) {
            //printf
            int idx;
            fscanf(in, "%d", &idx);
            printf("%s\n", strs[idx]);
        } else {
            //strlen
            int idx;
            char symb;
            fscanf(in, "%d %c", &idx, &symb);

            int count = 0;

            for (int i = 0; strs[idx][i]; i++) {
                if (strs[idx][i] == symb) {
                    count += 1;
                }
            }


            printf("%d\n", count);
        }
    }

    

    return 0;
}