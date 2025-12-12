#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct node {
    int val;
    int height;
    struct node *left;
    struct node *right;
} node;

int height(node *n) {
    return n ? n->height : 0;
}

int balanced(node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

node* newNode(int val) {
    node* node = malloc(sizeof(node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

node* rightRotate(node *y) {
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = MAX(height(y->left), height(y->right)) + 1;
    x->height = MAX(height(x->left), height(x->right)) + 1;

    return x;
}

node* leftRotate(node *x) {
    node *y = x->right;
    node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = MAX(height(x->left), height(x->right)) + 1;
    y->height = MAX(height(y->left), height(y->right)) + 1;

    return y;
}

node* push(node* node, int val, int *added) {
    if (!node) {
        *added = 1;
        return newNode(val);
    }

    if (val < node->val)
        node->left = push(node->left, val, added);
    else if (val > node->val)
        node->right = push(node->right, val, added);
    else {
        *added = 0; 
        return node;
    }

    node->height = 1 + MAX(height(node->left), height(node->right));
    int balance = balanced(node);

    if (balance > 1 && val < node->left->val)
        return rightRotate(node);

    if (balance < -1 && val > node->right->val)
        return leftRotate(node);

    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

node* minValueNode(node* n) {
    node* cur = n;
    while (cur && cur->left)
        cur = cur->left;
    return cur;
}

node* pop(node* head, int val, int *removed) {
    if (!head) {
        *removed = 0;
        return head;
    }

    if (val < head->val)
        head->left = pop(head->left, val, removed);
    else if (val > head->val)
        head->right = pop(head->right, val, removed);
    else {
        *removed = 1;
        if (!head->left || !head->right) {
            node* tmp = head->left ? head->left : head->right;
            if (!tmp) {
                tmp = head;
                head = NULL;
            } else {
                *head = *tmp;
            }
            free(tmp);
        } else {
            node* tmp = minValueNode(head->right);
            head->val = tmp->val;
            head->right = pop(head->right, tmp->val, removed);
        }
    }

    if (!head) return head;

    head->height = 1 + MAX(height(head->left), height(head->right));
    int balance = balanced(head);

    if (balance > 1 && balanced(head->left) >= 0)
        return rightRotate(head);

    if (balance > 1 && balanced(head->left) < 0) {
        head->left = leftRotate(head->left);
        return rightRotate(head);
    }

    if (balance < -1 && balanced(head->right) <= 0)
        return leftRotate(head);

    if (balance < -1 && balanced(head->right) > 0) {
        head->right = rightRotate(head->right);
        return leftRotate(head);
    }

    return head;
}

void lowerBound(node* head, int v, int *found, int *result) {
    node* current = head;
    *found = 0;
    *result = -1;

    while (current) {
        if (current->val >= v) {
            *found = 1;
            *result = current->val;
            current = current->left; 
        } else {
            current = current->right;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m;
    scanf("%d", &m);

    node* head = NULL;
    char op[10];
    int v;

    for (int i = 0; i < m; i++) {
        scanf("%s %d", op, &v);

        if (strcmp(op, "add") == 0) {
            int added;
            head = push(head, v, &added);
            printf("%s\n", added ? "added" : "dupe");
        } else if (strcmp(op, "remove") == 0) {
            int removed;
            head = pop(head, v, &removed);
            printf("%s\n", removed ? "removed" : "miss");
        } else if (strcmp(op, "lower") == 0) {
            int found, result;
            lowerBound(head, v, &found, &result);
            if (found) {
                printf("%d\n", result);
            } else {
                printf("###\n");
            }
        }
    }

    return 0;
}