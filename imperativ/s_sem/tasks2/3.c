#include <stdio.h>

typedef enum Mode {
    SEPARATING = 1,
    ALONE_ARG = 2,
    QUATS_ARG = 4
} Mode;

int main() {
    freopen("input.txt", "r", stdin);

    char c;
    Mode mode = SEPARATING;

    while ((c = getc(stdin)) != EOF) {
        switch (mode) {
            case SEPARATING: {
                if (c == ' ') {
                    break;  
                }
                
                printf("[");
                
                if (c == '\"') {
                    mode = QUATS_ARG;
                } else {
                    mode = ALONE_ARG;
                    printf("%c", c);
                }
                break;
            }

            case ALONE_ARG: {
                if (c == ' ') {
                    printf("]\n");
                    mode = SEPARATING;
                    break;
                }
                printf("%c", c);
                break;
            }

            case QUATS_ARG: {
                if (c == '\"') {
                    printf("]\n");
                    mode = SEPARATING;
                    break;
                }
                printf("%c", c);
                break;
            }
        }
    }

    if (mode & (ALONE_ARG | QUATS_ARG)) {
        printf("]");
    }
    
    return 0;
}