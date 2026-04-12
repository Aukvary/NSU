#include "list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

struct List {
    Node* head;
    Node* tail;
    size_t size;
    destroy_func_t destroy_func;
    print_func_t print_func;
};

List* list_create(void) {
    List* list = malloc(sizeof(List));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destroy_func = NULL;
    list->print_func = NULL;
    return list;
}

void list_set_destroy_func(List* list, destroy_func_t func) { 
    list->destroy_func = func;
}

void list_set_print_func(List* list, print_func_t func) {
    list->print_func = func;
}

void list_destroy(List* list) {
    if (!list) return;
    
    Node* current = list->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        if (list->destroy_func) {
            list->destroy_func(temp->data);
        }
        free(temp);
    }
    
    free(list);
}

bool list_push_front(List* list, int value) {
    if (!list) return false;
    
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return false;
    
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = list->head;
    
    if (list->head) {
        list->head->prev = new_node;
    } else {
        list->tail = new_node;
    }
    
    list->head = new_node;
    list->size++;
    return true;
}

bool list_push_back(List* list, int value) {
    if (!list) return false;
    
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return false;
    
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = list->tail;
    
    if (list->tail) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    
    list->tail = new_node;
    list->size++;
    return true;
}

bool list_pop_front(List* list, int* out_value) {
    if (!list || !list->head || !out_value) return false;
    
    Node* temp = list->head;
    *out_value = temp->data;
    
    list->head = list->head->next;
    
    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    
    free(temp);
    list->size--;
    return true;
}

bool list_pop_back(List* list, int* out_value) {
    if (!list || !list->tail || !out_value) return false;
    
    Node* temp = list->tail;
    *out_value = temp->data;
    
    list->tail = list->tail->prev;
    
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    
    free(temp);
    list->size--;
    return true;
}

size_t list_size(List* list) {
    return list ? list->size : 0;
}

bool list_is_empty(List* list) {
    return list ? list->size == 0 : 1;
}

void list_clear(List* list) {
    if (!list) return;
    
    Node* current = list->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        if (list->destroy_func) {
            list->destroy_func(temp->data);
        }
        free(temp);
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int* list_at(List* list, size_t index) {
    if (!list || index >= list->size) return NULL;
    
    Node* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    return &current->data;
}

int list_find(List* list, int value) {
    if (!list) return -1;
    
    Node* current = list->head;
    size_t index = 0;
    
    while (current) {
        if (current->data == value) {
            return (int)index;
        }
        current = current->next;
        index++;
    }
    
    return -1;
}

bool list_insert_at(List* list, size_t index, int value) {
    if (!list) return false;
    if (index > list->size) return false;
    
    if (index == 0) {
        return list_push_front(list, value);
    }
    
    if (index == list->size) {
        return list_push_back(list, value);
    }
    
    Node* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return false;
    
    new_node->data = value;
    new_node->prev = current->prev;
    new_node->next = current;
    
    current->prev->next = new_node;
    current->prev = new_node;
    
    list->size++;
    return true;
}

bool list_remove_at(List* list, size_t index, int* out_value) {
    if (!list || !out_value) return false;
    if (index >= list->size) return false;
    
    if (index == 0) {
        return list_pop_front(list, out_value);
    }
    
    if (index == list->size - 1) {
        return list_pop_back(list, out_value);
    }
    
    Node* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    *out_value = current->data;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    
    if (list->destroy_func) {
        list->destroy_func(current->data);
    }
    
    free(current);
    list->size--;
    return true;
}

static void merge_sort(Node** head_ref) {
    if (!head_ref || !*head_ref || !(*head_ref)->next) return;
    
    Node* slow = *head_ref;
    Node* fast = (*head_ref)->next;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    Node* right = slow->next;
    slow->next = NULL;
    if (right) right->prev = NULL;
    
    merge_sort(head_ref);
    merge_sort(&right);
    
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;
    
    Node* left_node = *head_ref;
    Node* right_node = right;
    
    while (left_node && right_node) {
        if (left_node->data <= right_node->data) {
            tail->next = left_node;
            left_node->prev = tail;
            left_node = left_node->next;
        } else {
            tail->next = right_node;
            right_node->prev = tail;
            right_node = right_node->next;
        }
        tail = tail->next;
    }
    
    if (left_node) {
        tail->next = left_node;
        left_node->prev = tail;
    }
    
    if (right_node) {
        tail->next = right_node;
        right_node->prev = tail;
    }
    
    *head_ref = dummy.next;
    if (*head_ref) (*head_ref)->prev = NULL;
    
    while (tail->next) tail = tail->next;
}

void list_sort(List* list) {
    if (!list || list->size < 2) return;
    
    merge_sort(&list->head);
    
    list->tail = list->head;
    while (list->tail && list->tail->next) {
        list->tail = list->tail->next;
    }
}

void list_print(List* list) {
    if (!list) {
        printf("[]");
        return;
    }
    
    if (list->print_func) {
        printf("[");
        Node* current = list->head;
        while (current) {
            list->print_func(current->data);
            if (current->next) printf(", ");
            current = current->next;
        }
        printf("]");
    } else {
        printf("[");
        Node* current = list->head;
        while (current) {
            printf("%d", current->data);
            if (current->next) printf(", ");
            current = current->next;
        }
        printf("]");
    }
}