#include "queue.h"
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

struct queue_t {
    node_t* head;
    node_t* tail;
    int size;
};

queue_t* queue_new() {
    queue_t* queue = malloc(sizeof(queue_t));
    if (!queue) return NULL;
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

void queue_free(queue_t* queue) {
    if (!queue) return;
    queue_clear(queue);
    free(queue);
}

bool queue_push(queue_t* queue, int value) {
    if (!queue) return false;
    node_t* new_node = malloc(sizeof(node_t));
    if (!new_node) return false;
    new_node->value = value;
    new_node->next = NULL;
    if (queue->tail) {
        queue->tail->next = new_node;
    } else {
        queue->head = new_node;
    }
    queue->tail = new_node;
    queue->size++;
    return true;
}

bool queue_pop(queue_t* queue, int* out) {
    if (!queue || !queue->head || !out) return false;
    node_t* temp = queue->head;
    *out = temp->value;
    queue->head = queue->head->next;
    if (!queue->head) queue->tail = NULL;
    free(temp);
    queue->size--;
    return true;
}

bool queue_peek(queue_t* queue, int* out) {
    if (!queue || !queue->head || !out) return false;
    *out = queue->head->value;
    return true;
}

bool queue_is_empty(queue_t* queue) {
    if (!queue) return true;
    return queue->head == NULL;
}

int queue_size(queue_t* queue) {
    if (!queue) return 0;
    return queue->size;
}

void queue_clear(queue_t* queue) {
    if (!queue) return;
    while (queue->head) {
        node_t* temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }
    queue->tail = NULL;
    queue->size = 0;
}