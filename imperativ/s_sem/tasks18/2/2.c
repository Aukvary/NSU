#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct State {
    char *regs[256];
} State;

void print_trimmed(const char *str) {
    if (!str) return;
    const char *start = str;
    while (isspace(*start)) start++;
    if (*start == '\0') return;
    while (*str) {
        if (*str == '\0') break;
        if (*str == ' ') {
            str++;
            continue;
        }

        putchar(*str);
        str++;
    }
}

void echo_0(State *state) {
    printf("ECHO:\n");
}

void echo_1(State *state, char *arg0) {
    printf("ECHO: ");
    print_trimmed(arg0);
    printf("\n");
}

void echo_2(State *state, char *arg0, char *arg1) {
    printf("ECHO: ");
    print_trimmed(arg0);
    printf("|");
    print_trimmed(arg1);
    printf("\n");
}

void echo_3(State *state, char *arg0, char *arg1, char *arg2) {
    printf("ECHO: ");
    print_trimmed(arg0);
    printf("|");
    print_trimmed(arg1);
    printf("|");
    print_trimmed(arg2);
    printf("\n");
}

void print_1(State *state, char *idx) {
    int i = atoi(idx);
    if (state->regs[i] != NULL) {
        print_trimmed(state->regs[i]);
        printf("\n");
    }
}

void printregs_0(State *state) {
    for (int i = 0; i < 256; i++) {
        if (state->regs[i] != NULL) {
            printf("%d = ", i);
            print_trimmed(state->regs[i]);
            printf("\n");
        }
    }
}

void store_2(State *state, char *idx, char *what) {
    int i = atoi(idx);
    if (state->regs[i] != NULL) {
        free(state->regs[i]);
    }
    state->regs[i] = strdup(what);
}

void copy_2(State *state, char *dst, char *src) {
    int d = atoi(dst);
    int s = atoi(src);
    if (state->regs[s] == NULL) return;
    if (d == s) return;
    if (state->regs[d] != NULL) {
        free(state->regs[d]);
    }
    state->regs[d] = strdup(state->regs[s]);
}

void clear_1(State *state, char *idx) {
    int i = atoi(idx);
    if (state->regs[i] != NULL) {
        free(state->regs[i]);
        state->regs[i] = NULL;
    }
}
