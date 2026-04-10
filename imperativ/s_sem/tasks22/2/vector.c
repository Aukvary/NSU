#include "vector.h"
#include <stdlib.h>
#include <string.h>

struct vector_t {
    int* data;
    size_t size;
    size_t capacity;
};

#define INIT_CAPACITY 4

static void ensure_capacity(vector_t* vec, size_t min_capacity) {
    if (min_capacity <= vec->capacity) return;
    
    size_t new_capacity = vec->capacity;
    if (new_capacity == 0) new_capacity = INIT_CAPACITY;
    while (new_capacity < min_capacity) {
        new_capacity *= 2;
    }
    
    int* new_data = (int*)realloc(vec->data, new_capacity * sizeof(int));
    if (new_data) {
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
}

vector_t* vector_create(void) {
    vector_t* vec = (vector_t*)malloc(sizeof(vector_t));
    if (!vec) return NULL;
    
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    
    return vec;
}

void vector_destroy(vector_t* vec) {
    if (vec) {
        free(vec->data);
        free(vec);
    }
}

void vector_push_back(vector_t* vec, int value) {
    if (!vec) return;
    ensure_capacity(vec, vec->size + 1);
    vec->data[vec->size++] = value;
}

void vector_pop_back(vector_t* vec) {
    if (!vec || vec->size == 0) return;
    vec->size--;
}

size_t vector_size(const vector_t* vec) {
    return vec ? vec->size : 0;
}

size_t vector_capacity(const vector_t* vec) {
    return vec ? vec->capacity : 0;
}

bool vector_at(const vector_t* vec, size_t index, int* out_value) {
    if (!vec || index >= vec->size) return false;
    if (out_value) *out_value = vec->data[index];
    return true;
}

bool vector_front(const vector_t* vec, int* out_value) {
    if (!vec || vec->size == 0) return false;
    if (out_value) *out_value = vec->data[0];
    return true;
}

bool vector_back(const vector_t* vec, int* out_value) {
    if (!vec || vec->size == 0) return false;
    if (out_value) *out_value = vec->data[vec->size - 1];
    return true;
}

void vector_resize(vector_t* vec, size_t new_size, int default_value) {
    if (!vec) return;
    
    if (new_size > vec->size) {
        ensure_capacity(vec, new_size);
        for (size_t i = vec->size; i < new_size; i++) {
            vec->data[i] = default_value;
        }
    }
    vec->size = new_size;
}

void vector_clear(vector_t* vec) {
    if (vec) vec->size = 0;
}

bool vector_empty(const vector_t* vec) {
    return vec ? vec->size == 0 : true;
}

const int* vector_data(const vector_t* vec) {
    return vec ? vec->data : NULL;
}

void vector_reserve(vector_t* vec, size_t new_capacity) {
    if (!vec || new_capacity <= vec->capacity) return;
    
    int* new_data = (int*)realloc(vec->data, new_capacity * sizeof(int));
    if (new_data) {
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
}