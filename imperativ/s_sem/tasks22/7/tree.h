#ifndef TREE_H
#define TREE_H

#include <jni.h>

typedef struct rb_tree rb_tree_t;

rb_tree_t* rb_create(void);
void rb_destroy(rb_tree_t* tree);
int rb_insert(rb_tree_t* tree, int key, jlong value);
jlong rb_find(rb_tree_t* tree, int key);
int rb_remove(rb_tree_t* tree, int key);
int rb_size(rb_tree_t* tree);
int rb_is_empty(rb_tree_t* tree);
void rb_clear(rb_tree_t* tree);
char* rb_to_string(rb_tree_t* tree);

#endif