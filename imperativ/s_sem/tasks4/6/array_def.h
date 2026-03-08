#if defined(TYPE) && defined(NAME)

#include <stdlib.h>
#include <string.h>
#define CONCAT(a, b) a##b
#define CONCAT2(a, b) CONCAT(a, b)
#define DEF_FUNC(name) CONCAT2(NAME, _##name)

#ifndef ARRAY_INITIAL_CAPACITY
#define ARRAY_INITIAL_CAPACITY 4
#endif

static int DEF_FUNC(grow)(NAME *vec, int min_cap) {
    if (vec->cap >= min_cap) return 0;
    
    int new_cap = vec->cap > 0 ? vec->cap : ARRAY_INITIAL_CAPACITY;
    while (new_cap < min_cap) {
        new_cap *= 2;
    }
    
    TYPE *new_arr = (TYPE*)realloc(vec->arr, new_cap * sizeof(TYPE));
    if (!new_arr) return -1;
    
    vec->arr = new_arr;
    vec->cap = new_cap;
    return 0;
}

void DEF_FUNC(init)(NAME *vec) {
    vec->n = 0;
    vec->cap = ARRAY_INITIAL_CAPACITY;
    vec->arr = (TYPE*)malloc(vec->cap * sizeof(TYPE));

    if (!vec->arr) {
        vec->cap = 0;
    }
}

void DEF_FUNC(destroy)(NAME *vec) {
    if (vec->arr) {
        free(vec->arr);
        vec->arr = NULL;
    }
    vec->n = 0;
    vec->cap = 0;
}

int DEF_FUNC(push)(NAME *vec, TYPE value) {
    if (DEF_FUNC(grow)(vec, vec->n + 1) < 0) return -1;
    vec->arr[vec->n] = value;
    return vec->n++;
}

TYPE DEF_FUNC(pop)(NAME *vec) {
    return vec->arr[--vec->n];
}

void DEF_FUNC(reserve)(NAME *vec, int cap) {
    if (cap <= vec->cap) return;
    DEF_FUNC(grow)(vec, cap);
}

void DEF_FUNC(resize)(NAME *vec, int newCnt, TYPE fill) {
    if (newCnt < 0) return;

    if (newCnt > vec->n) {
        DEF_FUNC(grow)(vec, newCnt);
        for (int i = vec->n; i < newCnt; i++) {
            vec->arr[i] = fill;
        }
    }
    vec->n = newCnt;
}

void DEF_FUNC(insert)(NAME *vec, int where, const TYPE *arr, int num) {
    if (num <= 0) return;
    if (where < 0) where = 0;
    if (where > vec->n) where = vec->n;

    DEF_FUNC(grow)(vec, vec->n + num);

    if (where < vec->n) {
        memmove(vec->arr + where + num, vec->arr + where, 
                (vec->n - where) * sizeof(TYPE));
    }
    
    for (int i = 0; i < num; i++) {
        vec->arr[where + i] = arr[i];
    }
    
    vec->n += num;
}

void DEF_FUNC(erase)(NAME *vec, int where, int num) {
    if (num <= 0 || where >= vec->n) return;
    if (where < 0) where = 0;
    if (where + num > vec->n) num = vec->n - where;
    
    if (where + num < vec->n) {
        memmove(vec->arr + where, vec->arr + where + num,
                (vec->n - where - num) * sizeof(TYPE));
    }
    
    vec->n -= num;
}

#undef CONCAT
#undef CONCAT2
#undef DEF_FUNC
#undef TYPE
#undef NAME

#endif