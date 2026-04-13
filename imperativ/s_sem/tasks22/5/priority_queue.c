#include "priority_queue.h"
#include <stdlib.h>
#include <string.h>

struct priority_queue {
    pq_item_t *items;
    size_t capacity;
    size_t size;
};

static void swap(pq_item_t *a, pq_item_t *b) {
    pq_item_t temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(priority_queue_t *queue, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (queue->items[parent].priority >= queue->items[index].priority)
            break;
        swap(&queue->items[parent], &queue->items[index]);
        index = parent;
    }
}

static void heapify_down(priority_queue_t *queue, size_t index) {
    size_t left, right, largest;
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;

        if (left < queue->size && queue->items[left].priority > queue->items[largest].priority)
            largest = left;
        if (right < queue->size && queue->items[right].priority > queue->items[largest].priority)
            largest = right;

        if (largest == index)
            break;

        swap(&queue->items[index], &queue->items[largest]);
        index = largest;
    }
}

priority_queue_t *pq_create(size_t capacity) {
    if (capacity == 0) return NULL;
    priority_queue_t *queue = (priority_queue_t *)malloc(sizeof(priority_queue_t));
    if (!queue) return NULL;
    queue->items = (pq_item_t *)malloc(sizeof(pq_item_t) * capacity);
    if (!queue->items) {
        free(queue);
        return NULL;
    }
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

void pq_destroy(priority_queue_t *queue, pq_free_func free_func) {
    if (!queue) return;
    if (free_func) {
        for (size_t i = 0; i < queue->size; ++i) {
            if (queue->items[i].data)
                free_func(queue->items[i].data);
        }
    }
    if (queue->items)
        free(queue->items);
    free(queue);
}

bool pq_push(priority_queue_t *queue, void *data, int priority) {
    if (!queue || !data) return false;
    if (queue->size >= queue->capacity) return false;
    
    queue->items[queue->size].data = data;
    queue->items[queue->size].priority = priority;
    queue->size++;
    heapify_up(queue, queue->size - 1);
    return true;
}

bool pq_pop(priority_queue_t *queue, void **data, int *priority) {
    if (!queue || queue->size == 0) return false;
    
    if (data) *data = queue->items[0].data;
    if (priority) *priority = queue->items[0].priority;
    
    queue->size--;
    
    if (queue->size > 0) {
        // Копируем последний элемент в корень
        queue->items[0] = queue->items[queue->size];
        // Очищаем последний элемент (опционально, для безопасности)
        queue->items[queue->size].data = NULL;
        queue->items[queue->size].priority = 0;
        heapify_down(queue, 0);
    } else {
        // Если очередь стала пустой, очищаем корневой элемент
        queue->items[0].data = NULL;
        queue->items[0].priority = 0;
    }
    
    return true;
}

bool pq_peek(priority_queue_t *queue, void **data, int *priority) {
    if (!queue || queue->size == 0) return false;
    if (data) *data = queue->items[0].data;
    if (priority) *priority = queue->items[0].priority;
    return true;
}

size_t pq_size(const priority_queue_t *queue) {
    return queue ? queue->size : 0;
}

bool pq_is_empty(const priority_queue_t *queue) {
    return queue ? queue->size == 0 : true;
}

bool pq_is_full(const priority_queue_t *queue) {
    return queue ? queue->size >= queue->capacity : false;
}

void pq_clear(priority_queue_t *queue, pq_free_func free_func) {
    if (!queue) return;
    if (free_func) {
        for (size_t i = 0; i < queue->size; ++i) {
            if (queue->items[i].data)
                free_func(queue->items[i].data);
        }
    }
    queue->size = 0;
    for (size_t i = 0; i < queue->capacity; i++) {
        queue->items[i].data = NULL;
        queue->items[i].priority = 0;
    }
}