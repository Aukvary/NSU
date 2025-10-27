#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000001
#define STRLEN 10

typedef struct Node {
    char str[STRLEN];
    struct Node* next;
} Node;

Node* head[SIZE];
Node* tail[SIZE];

void push(int key, char* word) {
    Node* new_node = malloc(sizeof(Node));
    strcpy(new_node->str, word);
    new_node->next = NULL;
    
    if (head[key] == NULL) {
        head[key] = new_node;
        tail[key] = new_node;
    } else {
        tail[key]->next = new_node;
        tail[key] = new_node;
    }
}

void output() {
    for (int i = 0; i < SIZE; i++) {
        Node* current = head[i];
        while (current != NULL) {
            printf("%d %s\n", i, current->str);
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        head[i] = NULL;
        tail[i] = NULL;
    }
}

int main() {
    int count;
    scanf("%d", &count);
    
    for (int i = 0; i < SIZE; i++) {
        head[i] = NULL;
        tail[i] = NULL;
    }
    
    for (int i = 0; i < count; i++) {
        int key;
        char word[STRLEN];
        scanf("%d %s", &key, word);
        push(key, word);
    }
    
    output();
    
    return 0;
}