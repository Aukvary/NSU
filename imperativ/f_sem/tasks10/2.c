#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1000001

typedef struct {
    int count;
    int capacity;
    char data[][8];
} vec;

vec* new_vec(int count) {
    vec* v = malloc(sizeof(vec) + 8 * count);

    v->count = 0;
    v->capacity = count;

    return v;
}

void add(vec** v, char* s) {
    if ((*v)->count == (*v)->capacity) {
        size_t new_capacity = (*v)->capacity == 0 ? 1 : (*v)->capacity * 2;
        *v = realloc((*v), sizeof(vec) + new_capacity * 8);

        (*v)->capacity = new_capacity;
    }

    strcpy((*v)->data[(*v)->count++], s);
}

vec* values[SIZE] = { NULL };

int main() {
    int n;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d", &n);

    for (int i = 0; i < n; i++) {
        char tmp[8] = { 0 };
        int idx;
        fscanf(in, "%d %s", &idx, tmp);
        if (values[idx] == NULL) {
            values[idx] = new_vec(10);
        }

        add(&values[idx], tmp);
    }

    for (int i = 0; i < SIZE; i++) {
        if (values[i] == NULL) continue;
        for (int j = 0; j < values[i]->count; j++) {
            printf("%d %s\n", i, values[i]->data[j]);
        }
    }
}
