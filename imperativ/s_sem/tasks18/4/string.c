#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct State {
    char *regs[256];
} State;

void concat_2(State *state, char *idx0, char *idx1) {
    int i = atoi(idx0);
    int j = atoi(idx1);
    if (state->regs[i] == NULL || state->regs[j] == NULL) return;

    size_t len_a = strlen(state->regs[i]);
    size_t len_b = strlen(state->regs[j]);
    char *new_str = malloc(len_a + len_b + 1);
    
    strcpy(new_str, state->regs[i]);
    strcat(new_str, state->regs[j]);

    free(state->regs[i]);
    state->regs[i] = new_str;
}

void tokenize_1(State *state, char *arg) {
    char *s = strdup(arg);
    char *token = strtok(s, "_");
    int count = 0;

    while (token != NULL) {
        count++;
        int reg_idx = count;
        if (state->regs[reg_idx]) free(state->regs[reg_idx]);
        state->regs[reg_idx] = strdup(token);
        token = strtok(NULL, "_");
    }

    char buf[16];
    sprintf(buf, "%d", count);
    if (state->regs[0]) free(state->regs[0]);
    state->regs[0] = strdup(buf);
    
    free(s);
}