#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decls.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

EXPORT
void echo_0(State *state) {
    printf("ECHO: \n");
    fflush(stdout);
}

EXPORT
void echo_1(State *state, char *arg0) {
    printf("ECHO: %s\n", arg0);
    fflush(stdout);
}

EXPORT
void echo_2(State *state, char *arg0, char *arg1) {
    printf("ECHO: %s|%s\n", arg0, arg1);
    fflush(stdout);
}

EXPORT
void echo_3(State *state, char *arg0, char *arg1, char *arg2) {
    printf("ECHO: %s|%s|%s\n", arg0, arg1, arg2);
    fflush(stdout);
}

EXPORT
void print_1(State *state, char *idx) {
    int index = atoi(idx);

    if (state->regs[index] != NULL) {
        printf("%s\n", state->regs[index]);
        fflush(stdout);
    }
}

EXPORT
void printregs_0(State *state) {
    for (int i = 0; i < 256; i++) {
        if (state->regs[i] == NULL) continue;
        printf("%d = %s\n", i, state->regs[i]);
        fflush(stdout);
    }
}

EXPORT
void store_2(State *state, char *idx, char *what) {
    int index = atoi(idx);

    if (state->regs[index] != NULL)
        free(state->regs[index]);

    state->regs[index] = malloc(strlen(what) + 1);
    strcpy(state->regs[index], what);
}

EXPORT
void copy_2(State *state, char *dst, char *src) {
    int destination = atoi(dst);
    int source = atoi(src);

    if (destination == source)
        return;

    if (state->regs[destination] != NULL)
        free(state->regs[destination]);

    state->regs[destination] = malloc(strlen(state->regs[source]) + 1);
    strcpy(state->regs[destination], state->regs[source]);

}

EXPORT
void clear_1(State *state, char *idx) {
    int index = atoi(idx);

    if (state->regs[index] != NULL) {
        free(state->regs[index]);
        state->regs[index] = NULL;
    }
}