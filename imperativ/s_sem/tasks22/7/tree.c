#include "tree.h"
#include "tree_p.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

rb_node_t* create_node(int key, jlong value) {
    rb_node_t* node = (rb_node_t*)malloc(sizeof(rb_node_t));
    node->key = key;
    node->value = value;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void destroy_subtree(rb_node_t* node) {
    if (node == NULL) return;
    destroy_subtree(node->left);
    destroy_subtree(node->right);
    free(node);
}

rb_tree_t* rb_create(void) {
    rb_tree_t* tree = (rb_tree_t*)malloc(sizeof(rb_tree_t));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void rb_destroy(rb_tree_t* tree) {
    if (tree == NULL) return;
    destroy_subtree(tree->root);
    free(tree);
}

void rotate_left(rb_tree_t* tree, rb_node_t* x) {
    rb_node_t* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotate_right(rb_tree_t* tree, rb_node_t* x) {
    rb_node_t* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
}

void fix_insert(rb_tree_t* tree, rb_node_t* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            rb_node_t* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_right(tree, z->parent->parent);
            }
        } else {
            rb_node_t* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_left(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

int rb_insert(rb_tree_t* tree, int key, jlong value) {
    rb_node_t* z = create_node(key, value);
    rb_node_t* y = NULL;
    rb_node_t* x = tree->root;
    
    while (x != NULL) {
        y = x;
        if (key < x->key)
            x = x->left;
        else if (key > x->key)
            x = x->right;
        else {
            // Ключ уже существует
            free(z);
            return 0;
        }
    }
    
    z->parent = y;
    if (y == NULL)
        tree->root = z;
    else if (key < y->key)
        y->left = z;
    else
        y->right = z;
    
    fix_insert(tree, z);
    tree->size++;
    return 1;
}

rb_node_t* find_node(rb_node_t* root, int key) {
    while (root != NULL) {
        if (key < root->key)
            root = root->left;
        else if (key > root->key)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

jlong rb_find(rb_tree_t* tree, int key) {
    rb_node_t* node = find_node(tree->root, key);
    return node ? node->value : 0;
}

rb_node_t* minimum_node(rb_node_t* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

void transplant(rb_tree_t* tree, rb_node_t* u, rb_node_t* v) {
    if (u->parent == NULL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

void fix_remove(rb_tree_t* tree, rb_node_t* x) {
    while (x != tree->root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            rb_node_t* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate_left(tree, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL)
                        w->left->color = BLACK;
                    w->color = RED;
                    rotate_right(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL)
                    w->right->color = BLACK;
                rotate_left(tree, x->parent);
                x = tree->root;
            }
        } else {
            rb_node_t* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate_right(tree, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL)
                        w->right->color = BLACK;
                    w->color = RED;
                    rotate_left(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL)
                    w->left->color = BLACK;
                rotate_right(tree, x->parent);
                x = tree->root;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

int rb_remove(rb_tree_t* tree, int key) {
    rb_node_t* z = find_node(tree->root, key);
    if (z == NULL) return 0;
    
    rb_node_t* y = z;
    rb_node_t* x = NULL;
    color_t y_original_color = y->color;
    
    if (z->left == NULL) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = minimum_node(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) x->parent = y;
        } else {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    
    if (y_original_color == BLACK)
        fix_remove(tree, x);
    
    free(z);
    tree->size--;
    return 1;
}

int rb_size(rb_tree_t* tree) {
    return tree->size;
}

int rb_is_empty(rb_tree_t* tree) {
    return tree->size == 0;
}

void rb_clear(rb_tree_t* tree) {
    destroy_subtree(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

void inorder_string(rb_node_t* node, char* buffer, int* pos, int* first) {
    if (node == NULL) return;
    inorder_string(node->left, buffer, pos, first);
    if (*first) {
        *first = 0;
        *pos += sprintf(buffer + *pos, "(%d,%ld)", node->key, (long)node->value);
    } else {
        *pos += sprintf(buffer + *pos, " (%d,%ld)", node->key, (long)node->value);
    }
    inorder_string(node->right, buffer, pos, first);
}

char* rb_to_string(rb_tree_t* tree) {
    if (tree->root == NULL) {
        char* empty = (char*)malloc(5);
        strcpy(empty, "empty");
        return empty;
    }
    char* buffer = (char*)malloc(4096);
    int pos = 0;
    int first = 1;
    inorder_string(tree->root, buffer, &pos, &first);
    return buffer;
}