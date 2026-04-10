#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vector_t vector_t;

vector_t* vector_create(void);
void vector_destroy(vector_t* vec);
void vector_push_back(vector_t* vec, int value);
void vector_pop_back(vector_t* vec);
size_t vector_size(const vector_t* vec);
size_t vector_capacity(const vector_t* vec);
bool vector_at(const vector_t* vec, size_t index, int* out_value);
bool vector_front(const vector_t* vec, int* out_value);
bool vector_back(const vector_t* vec, int* out_value);
void vector_resize(vector_t* vec, size_t new_size, int default_value);
void vector_clear(vector_t* vec);
bool vector_empty(const vector_t* vec);
const int* vector_data(const vector_t* vec);
void vector_reserve(vector_t* vec, size_t new_capacity);

#ifdef __cplusplus
}
#endif

#endif