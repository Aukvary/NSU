#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node_s {
    int data;
    struct node_s* next;
    struct node_s* next_big;
    int big_step;
} node;

node* head = NULL;
int len = 0;

node* new_node(int data, int big) {
    node* new_node = malloc(sizeof(node));

    *new_node = (node) {
        .data = data,
        .next = NULL,
        .next_big = (void*)(long long)big,
        .big_step = 0
    };

    return new_node;
}

node* get(int k) {    
    node* cur = head;
    int idx = 0;
    
    while (idx < k) {
        if (cur->next_big && idx + cur->big_step <= k) {
            idx += cur->big_step;
            cur = cur->next_big;
            continue;
        } 

        cur = cur->next;
        idx++;
    }
    
    return cur;
}

void push_node(int k, int data) {
    int big_step_size = (int)sqrt(len + 1);
    if (big_step_size < 1) big_step_size = 1;
    
    int is_big = (rand() % big_step_size == 0);
    node* n = new_node(data, is_big);
    
    if (head == NULL) {
        head = n;
        len++;
        return;
    }
    
    if (k == 0) {
        n->next = head;
        head = n;
        len++;
        return;
    }
    
    node* prev = get(k - 1);
    if (prev != NULL) {
        n->next = prev->next;
        prev->next = n;
        len++;
    }
}

void cange_Links() {
    int big_step_size = (int)sqrt(len);
    if (big_step_size < 1) return;
    
    node* current = head;
    while (current) {
        if (!current->next_big) {
            current = current->next;
            continue;
        } 
        current->next_big = NULL;
        current->big_step = 0;
        
        node* temp = current->next;
        int steps = 1;
        
        while (temp && steps <= big_step_size) {
            if (temp->next_big) {
                current->next_big = temp;
                current->big_step = steps;
                break;
            }
            temp = temp->next;
            steps++;
        }
        current = current->next;
    }
}

int main() {
    FILE* in = fopen("input.txt", "r");

    int n;
    fscanf(in, "%d", &n);
    
    for (int i = 0; i < n; i++) {
        int type;
        fscanf(in, "%d", &type);
        
        if (type) {
            int k;
            fscanf(in, "%d", &k);
            node* node = get(k);
            if (node) 
                printf("%d\n", node->data);
        } else {
            int k;
            int data;
            fscanf(in, "%d %d", &k, &data);
            push_node(k, data);
            cange_Links();
        }
    }
    
    return 0;
}