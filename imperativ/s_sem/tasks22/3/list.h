#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct List List;

typedef void (*destroy_func_t)(int value);
typedef void (*print_func_t)(int value);

List* list_create(void);
void list_destroy(List* list);

bool list_push_front(List* list, int value);
bool list_push_back(List* list, int value);
bool list_pop_front(List* list, int* out_value);
bool list_pop_back(List* list, int* out_value);
size_t list_size(List* list);
bool list_is_empty(List* list);
void list_clear(List* list);
int* list_at(List* list, size_t index);
int list_find(List* list, int value);
bool list_insert_at(List* list, size_t index, int value);
bool list_remove_at(List* list, size_t index, int* out_value);
void list_sort(List* list);
void list_print(List* list);

void list_set_destroy_func(List* list, destroy_func_t func);
void list_set_print_func(List* list, print_func_t func);

#endif