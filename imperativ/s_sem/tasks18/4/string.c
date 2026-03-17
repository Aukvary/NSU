#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

typedef struct State {
    char *regs[256];
} State;

static char* my_strdup(const char* s) {
    size_t len = strlen(s) + 1;
    char* res = (char*)malloc(len);
    if (res) memcpy(res, s, len);
    return res;
}

EXPORT void concat_2(State *state, char *idx0, char *idx1) {
    if (!state || !idx0 || !idx1) return;
    int i = atoi(idx0);
    int j = atoi(idx1);
    
    if (i < 0 || i > 255 || j < 0 || j > 255) return;
    if (!state->regs[i] || !state->regs[j]) return;

    if (i == j) {
        char *temp = my_strdup(state->regs[i]);
        size_t len = strlen(temp) * 2;
        char *new_str = (char *)malloc(len + 1);
        if (!new_str) {
            free(temp);
            return;
        }
        strcpy(new_str, temp);
        strcat(new_str, temp);
        free(state->regs[i]);
        state->regs[i] = new_str;
        free(temp);
    } else {
        size_t len_a = strlen(state->regs[i]);
        size_t len_b = strlen(state->regs[j]);
        
        char *new_str = (char *)malloc(len_a + len_b + 1);
        if (!new_str) return;

        memcpy(new_str, state->regs[i], len_a);
        memcpy(new_str + len_a, state->regs[j], len_b);
        new_str[len_a + len_b] = '\0';

        free(state->regs[i]);
        state->regs[i] = new_str;
    }
}

EXPORT void tokenize_1(State *state, char *arg) {
    if (!state || !arg) return;

    char *temp_str = my_strdup(arg);
    if (!temp_str) return;

    for (int i = 1; i < 256; i++) {
        if (state->regs[i]) {
            free(state->regs[i]);
            state->regs[i] = NULL;
        }
    }

    int count = 0;
    char *token = strtok(temp_str, "_");
    
    while (token != NULL && count < 255) {
        count++;
        state->regs[count] = my_strdup(token);
        token = strtok(NULL, "_");
    }

    char buf[32];
    sprintf(buf, "%d", count);
    if (state->regs[0]) free(state->regs[0]);
    state->regs[0] = my_strdup(buf);
    
    free(temp_str);
}