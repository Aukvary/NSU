#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct queue_t queue_t;

queue_t* queue_new();
void queue_free(queue_t* q);
bool queue_push(queue_t* q, int value);
bool queue_pop(queue_t* q, int* out);
bool queue_peek(queue_t* q, int* out);
bool queue_is_empty(queue_t* q);
int queue_size(queue_t* q);
void queue_clear(queue_t* q);

#endif