#include "priority_queue.h"
#include <stdlib.h>
#include <stdint.h>

struct priority_queue {
    pq_item_t *items;
    size_t size;
    size_t capacity; 
};

static void swap_items(pq_item_t *first, pq_item_t *second) {
    pq_item_t temporary = *first;
    *first = *second;
    *second = temporary;
}

static void heapify_up(priority_queue_t *queue, size_t child_index) {
    while (child_index > 0) {
        size_t parent_index = (child_index - 1) / 2;
        if (queue->items[parent_index].priority >= queue->items[child_index].priority) {
            break;
        }
        swap_items(&queue->items[parent_index], &queue->items[child_index]);
        child_index = parent_index;
    }
}

static void heapify_down(priority_queue_t *queue, size_t parent_index) {
    while (1) {
        size_t left_child = 2 * parent_index + 1;
        size_t right_child = 2 * parent_index + 2;
        size_t largest_index = parent_index;

        if (left_child < queue->size && 
            queue->items[left_child].priority > queue->items[largest_index].priority) {
            largest_index = left_child;
        }
        if (right_child < queue->size && 
            queue->items[right_child].priority > queue->items[largest_index].priority) {
            largest_index = right_child;
        }

        if (largest_index == parent_index) break;
        
        swap_items(&queue->items[parent_index], &queue->items[largest_index]);
        parent_index = largest_index;
    }
}

static bool ensure_capacity(priority_queue_t *queue) {
    pq_item_t *new_storage;
    size_t new_capacity;

    if (queue->capacity != 0) return true;

    new_capacity = (queue->size == 0 ? 4 : queue->size * 2);
    if (new_capacity < queue->size) return false;

    new_storage = (pq_item_t *)realloc(queue->items, new_capacity * sizeof(pq_item_t));
    if (new_storage == NULL) return false;

    queue->items = new_storage;
    return true;
}

priority_queue_t *pq_create(size_t capacity) {
    priority_queue_t *queue;

    queue = (priority_queue_t *)malloc(sizeof(priority_queue_t));
    if (queue == NULL) return NULL;

    queue->size = 0;
    queue->capacity = capacity;
    queue->items = NULL;

    if (capacity > 0) {
        queue->items = (pq_item_t *)malloc(capacity * sizeof(pq_item_t));
        if (queue->items == NULL) {
            free(queue);
            return NULL;
        }
    }

    return queue;
}

void pq_clear(priority_queue_t *queue, pq_free_func free_func) {
    size_t index;

    if (queue == NULL) return;

    if (free_func != NULL) {
        for (index = 0; index < queue->size; index++) {
            free_func(queue->items[index].data);
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