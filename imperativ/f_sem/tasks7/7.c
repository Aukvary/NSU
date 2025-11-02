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
int list_length = 0;

node* new_node(int data, int big) {
    node* new_node = malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->next_big = (void*)(long long)big;
    new_node->big_step = 0;
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

void insert_node(int k, int data) {
    int big_step_size = (int)sqrt(list_length + 1);
    if (big_step_size < 1) big_step_size = 1;
    
    int is_big = (rand() % big_step_size == 0);
    node* n = new_node(data, is_big);
    
    if (head == NULL) {
        head = n;
        list_length++;
        return;
    }
    
    if (k == 0) {
        n->next = head;
        head = n;
        list_length++;
        return;
    }
    
    node* prev = get(k - 1);
    if (prev != NULL) {
        n->next = prev->next;
        prev->next = n;
        list_length++;
    }
}

void update_big_links() {
    int big_step_size = (int)sqrt(list_length);
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
        
        while (temp && steps <= big_step_size * 2) {
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
            insert_node(k, data);
            update_big_links();
        }
    }
    
    return 0;
}