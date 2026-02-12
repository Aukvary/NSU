#include <stdio.h>

typedef enum Mode {
    SEPARATING,
    ALONE_ARG,
    QUATS_ARG
} Mode;


int main() {
    freopen("input.txt", "r", stdin);

    char c;
    Mode mode = SEPARATING;

    while((c = getc(stdin)) != -1) {
        switch (mode)
        {
            case SEPARATING: {
                if (c == ' ') break;

                mode = (c == '\"') ? QUATS_ARG : ALONE_ARG;

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

    printf("]");
    
    return 0;
}