#ifndef PRIORITY_QUEUE_H 
#define PRIORITY_QUEUE_H 
#include <stddef.h> 
#include <stdbool.h> 
#ifdef __cplusplus 
extern "C" 
{ 
#endif 
    typedef struct 
    { 
        void *data; 
        int priority; 
    } pq_item_t; 
    typedef struct priority_queue priority_queue_t; 
    typedef void (*pq_free_func)(void *data); 
    priority_queue_t *pq_create(size_t capacity); 
    void pq_destroy(priority_queue_t *queue, pq_free_func free_func); 
    bool pq_push(priority_queue_t *queue, void *data, int priority); 
    bool pq_pop(priority_queue_t *queue, void **data, int *priority); 
    bool pq_peek(priority_queue_t *queue, void **data, int *priority); 
    size_t pq_size(const priority_queue_t *queue); 
    bool pq_is_empty(const priority_queue_t *queue); 
    bool pq_is_full(const priority_queue_t *queue); 
    void pq_clear(priority_queue_t *queue, pq_free_func free_func); 
#ifdef __cplusplus 
} 
#endif 
#endif // PRIORITY_QUEUE_H