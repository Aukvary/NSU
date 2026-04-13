#include "priority_queue.h"
#include <stdlib.h>
#include <stdint.h>

struct priority_queue {
    pq_item_t *items;
    size_t size;
    size_t capacity; /* 0 = unlimited */
};

static void swap_items(pq_item_t *a, pq_item_t *b) {
    pq_item_t t = *a;
    *a = *b;
    *b = t;
}

static void heapify_up(priority_queue_t *q, size_t i) {
    while (i > 0) {
        size_t p = (i - 1) / 2;
        if (q->items[p].priority >= q->items[i].priority) break;
        swap_items(&q->items[p], &q->items[i]);
        i = p;
    }
}

static void heapify_down(priority_queue_t *q, size_t i) {
    while (1) {
        size_t l = 2 * i + 1;
        size_t r = 2 * i + 2;
        size_t best = i;

        if (l < q->size && q->items[l].priority > q->items[best].priority)
            best = l;
        if (r < q->size && q->items[r].priority > q->items[best].priority)
            best = r;

        if (best == i) break;
        swap_items(&q->items[i], &q->items[best]);
        i = best;
    }
}

static bool ensure_capacity(priority_queue_t *q) {
    pq_item_t *tmp;
    size_t new_cap;

    if (q->capacity != 0) return true;

    new_cap = (q->size == 0 ? 4 : q->size * 2);
    if (new_cap < q->size) return false;

    tmp = (pq_item_t *)realloc(q->items, new_cap * sizeof(pq_item_t));
    if (tmp == NULL) return false;

    q->items = tmp;
    return true;
}

priority_queue_t *pq_create(size_t capacity) {
    priority_queue_t *q;

    q = (priority_queue_t *)malloc(sizeof(priority_queue_t));
    if (q == NULL) return NULL;

    q->size = 0;
    q->capacity = capacity;
    q->items = NULL;

    if (capacity > 0) {
        q->items = (pq_item_t *)malloc(capacity * sizeof(pq_item_t));
        if (q->items == NULL) {
            free(q);
            return NULL;
        }
    }

    return q;
}

void pq_clear(priority_queue_t *queue, pq_free_func free_func) {
    size_t i;

    if (queue == NULL) return;

    if (free_func != NULL) {
        for (i = 0; i < queue->size; i++) {
            free_func(queue->items[i].data);
        }
    }

    queue->size = 0;
}

void pq_destroy(priority_queue_t *queue, pq_free_func free_func) {
    if (queue == NULL) return;
    pq_clear(queue, free_func);
    free(queue->items);
    free(queue);
}

bool pq_push(priority_queue_t *queue, void *data, int priority) {
    if (queue == NULL) return false;

    if (queue->capacity == 0) {
        if (!ensure_capacity(queue)) return false;
    } else {
        if (queue->size >= queue->capacity) return false;
    }

    queue->items[queue->size].data = data;
    queue->items[queue->size].priority = priority;
    heapify_up(queue, queue->size);
    queue->size++;
    return true;
}

bool pq_pop(priority_queue_t *queue, void **data, int *priority) {
    if (queue == NULL || queue->size == 0) return false;

    if (data != NULL) *data = queue->items[0].data;
    if (priority != NULL) *priority = queue->items[0].priority;

    queue->size--;
    if (queue->size > 0) {
        queue->items[0] = queue->items[queue->size];
        heapify_down(queue, 0);
    }

    queue->items[queue->size].data = NULL;
    queue->items[queue->size].priority = 0;

    return true;
}

bool pq_peek(priority_queue_t *queue, void **data, int *priority) {
    if (queue == NULL || queue->size == 0) return false;

    if (data != NULL) *data = queue->items[0].data;
    if (priority != NULL) *priority = queue->items[0].priority;

    return true;
}

size_t pq_size(const priority_queue_t *queue) {
    if (queue == NULL) return 0;
    return queue->size;
}

bool pq_is_empty(const priority_queue_t *queue) {
    return pq_size(queue) == 0;
}

bool pq_is_full(const priority_queue_t *queue) {
    if (queue == NULL) return false;
    if (queue->capacity == 0) return false;
    return queue->size >= queue->capacity;
}