#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
    struct node* parent;
    int size;
} node;

typedef struct {
    node* root;
    int size;
    int max_size;
} ScapegoatTree;

#define ALPHA 0.7

node* new_node(int val) {
    node* new_node = malloc(sizeof(node));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    new_node->size = 1;
    return new_node;
}

void resize(node* n) {
    if (n == NULL) return;
    n->size = 1;
    if (n->left) n->size += n->left->size;
    if (n->right) n->size += n->right->size;
}

int unbalanced(node* n) {
    if (n == NULL) 
        return 0;

    int left_size = n->left ? n->left->size : 0;
    int right_size = n->right ? n->right->size : 0;
    return left_size > ALPHA * n->size || right_size > ALPHA * n->size;
}

void store(node* n, node** nodes, int* index) {
    if (n == NULL) 
        return;
        
    store(n->left, nodes, index);
    nodes[(*index)++] = n;
    store(n->right, nodes, index);
}

node* build_tree(node **nodes, int start, int end) {
    if (start > end) 
        return NULL;
    
    int mid = (start + end) / 2;
    node *current = nodes[mid];
    
    current->left = build_tree(nodes, start, mid - 1);
    if (current->left) current->left->parent = current;
    
    current->right = build_tree(nodes, mid + 1, end);
    if (current->right) current->right->parent = current;
    
    resize(current);
    return current;
}

void rebuild(ScapegoatTree *tree, node *scapegoat) {
    if (scapegoat == NULL) return;
    
    int n = scapegoat->size;
    node **nodes = (node**)malloc(n * sizeof(node*));
    int index = 0;
    
    store(scapegoat, nodes, &index);
    
    node *parent = scapegoat->parent;
    node *new_subtree = build_tree(nodes, 0, n - 1);
    
    if (parent == NULL) {
        tree->root = new_subtree;
        if (new_subtree) new_subtree->parent = NULL;
    } else if (parent->left == scapegoat) {
        parent->left = new_subtree;
        if (new_subtree) new_subtree->parent = parent;
    } else {
        parent->right = new_subtree;
        if (new_subtree) new_subtree->parent = parent;
    }
    
    free(nodes);
}

node* push_node(node *root, int val, node **scapegoat, node **parent_ptr, int *inserted) {
    if (root == NULL) {
        *inserted = 1;
        return new_node(val);
    }
    
    if (val == root->val) {
        *inserted = 0;
        return root;
    }
    
    node *new_node = NULL;
    if (val < root->val) {
        root->left = push_node(root->left, val, scapegoat, &root, inserted);
        if (root->left) root->left->parent = root;
        new_node = root->left;
    } else {
        root->right = push_node(root->right, val, scapegoat, &root, inserted);
        if (root->right) root->right->parent = root;
        new_node = root->right;
    }
    
    if (*inserted) {
        resize(root);
    }
    
    if (*inserted && *scapegoat == NULL && unbalanced(root)) {
        *scapegoat = root;
        *parent_ptr = root->parent;
    }
    
    return root;
}

void push(ScapegoatTree *tree, int val) {
    node* scapegoat = NULL;
    node* parent = NULL;
    int inserted = 0;
    
    tree->root = push_node(tree->root, val, &scapegoat, &parent, &inserted);
    
    if (inserted) {
        tree->size++;
        tree->max_size = tree->size > tree->max_size ? tree->size : tree->max_size;
    }
    
    if (scapegoat != NULL) {
        rebuild(tree, scapegoat);
    }
}

int search(node *root, int val) {
    node* current = root;
    while (current != NULL) {
        if (val == current->val) {
            return 1;
        } else if (val < current->val) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return 0;
}

void print(node *n, int *first) {
    if (n == NULL) return;
    
    print(n->left, first);
    
    if (!(*first)) {
        printf(" ");
    }
    printf("%d", n->val);
    *first = 0;
    
    print(n->right, first);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int q;
    scanf("%d", &q);
    
    ScapegoatTree tree = {NULL, 0, 0};
    
    for (int i = 0; i < q; i++) {
        char op[2];
        int x;
        
        scanf("%1s", op);
        
        if (op[0] == '+') {
            scanf("%d", &x);
            push(&tree, x);
        } else if (op[0] == '?') {
            scanf("%d", &x);
            if (search(tree.root, x)) {
                printf("Found\n");
            } else {
                printf("Not found\n");
            }
        } else if (op[0] == 'p') {
            int first = 1;
            print(tree.root, &first);
            printf("\n");
        }
    }
    
    return 0;
}