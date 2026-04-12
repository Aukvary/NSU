#ifndef TREE_P_H
#define TREE_P_H

typedef enum { RED, BLACK } color_t;

typedef struct rb_node {
    int key;
    jlong value;
    color_t color;
    struct rb_node *left, *right, *parent;
} rb_node_t;

struct rb_tree {
    rb_node_t* root;
    int size;
};

// Вспомогательные функции
rb_node_t* create_node(int key, jlong value);
void destroy_subtree(rb_node_t* node);
void rotate_left(rb_tree_t* tree, rb_node_t* node);
void rotate_right(rb_tree_t* tree, rb_node_t* node);
void fix_insert(rb_tree_t* tree, rb_node_t* node);
void fix_remove(rb_tree_t* tree, rb_node_t* node);
rb_node_t* find_node(rb_node_t* root, int key);
rb_node_t* minimum_node(rb_node_t* node);
void transplant(rb_tree_t* tree, rb_node_t* u, rb_node_t* v);
void inorder_string(rb_node_t* node, char* buffer, int* pos, int* first);

#endif