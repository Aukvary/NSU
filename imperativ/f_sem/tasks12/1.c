#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct node {
    struct node* left;
    struct node* right;

    int val;
    int count;
} node;

node* create_node(int val) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->val = val;
    new_node->count = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert(node** root, int val) {
    if (*root == NULL) {
        *root = create_node(val);
        return;
    }
    if (val < (*root)->val) {
        insert(&((*root)->left), val);
    } else if (val > (*root)->val) {
        insert(&((*root)->right), val);
    } else {
        (*root)->count++;
    }
}

void print(node* root, FILE* out) {
    if (root == NULL) return;
    print(root->left, out);
    for (int i = 0; i < root->count; i++) {
        fwrite(&root->val, sizeof(int), 1, out);
    }
    print(root->right, out);
}

int main() {
    FILE* in = fopen("input.txt", "rb");
    FILE* out = fopen("output.txt", "wb");

    int32_t n;
    fread(&n, sizeof(n), 1, in);

    node* head = NULL;
    for (int i = 0; i < n; i++) {
        int value;
        fread(&value, sizeof(int), 1, in);
        insert(&head, value);
    }

    print(head, out);
}