#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int value;
    int is_big;
    struct Node* next;
    struct Node* next_big;
    int big_step;
} Node;

Node* head = NULL;
int list_length = 0;

Node* create_node(int value, int is_big) {
    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->is_big = is_big;
    new_node->next = NULL;
    new_node->next_big = NULL;
    new_node->big_step = 0;
    return new_node;
}

Node* find_node(int k) {
    if (head == NULL) return NULL;
    
    Node* current = head;
    int idx = 0;
    
    while (current != NULL && idx < k) {
        if (current->is_big && current->next_big != NULL && 
            idx + current->big_step <= k) {
            idx += current->big_step;
            current = current->next_big;
        } else {
            current = current->next;
            idx++;
        }
    }
    
    return current;
}

void insert_node(int k, int value) {
    int big_step_size = (int)sqrt(list_length + 1);
    if (big_step_size < 1) big_step_size = 1;
    
    int is_big = (rand() % big_step_size == 0);
    Node* new_node = create_node(value, is_big);
    
    if (head == NULL) {
        head = new_node;
        list_length++;
        return;
    }
    
    if (k == 0) {
        new_node->next = head;
        head = new_node;
        list_length++;
        return;
    }
    
    Node* prev = find_node(k - 1);
    if (prev != NULL) {
        new_node->next = prev->next;
        prev->next = new_node;
        list_length++;
    }
}

void update_big_links() {
    int big_step_size = (int)sqrt(list_length);
    if (big_step_size < 1) return;
    
    Node* current = head;
    while (current != NULL) {
        if (current->is_big) {
            current->next_big = NULL;
            current->big_step = 0;
            
            Node* temp = current->next;
            int steps = 1;
            
            while (temp != NULL && steps <= big_step_size * 2) {
                if (temp->is_big) {
                    current->next_big = temp;
                    current->big_step = steps;
                    break;
                }
                temp = temp->next;
                steps++;
            }
        }
        current = current->next;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        int type;
        scanf("%d", &type);
        
        if (type == 0) {
            int k, value;
            scanf("%d %d", &k, &value);
            insert_node(k, value);
            update_big_links();
        } else {
            int k;
            scanf("%d", &k);
            Node* node = find_node(k);
            if (node != NULL) {
                printf("%d\n", node->value);
            }
        }
    }
    
    return 0;
}