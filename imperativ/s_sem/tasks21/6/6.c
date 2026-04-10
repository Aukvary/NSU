#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* prev;
} Node;

Node* versions[500005];

Node* create_node(int val, Node* prev_node) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = val;
    new_node->prev = prev_node;
    return new_node;
}

void print_stack(Node* node) {
    if (node == NULL) {
        printf("-");
    } else {
        while (node != NULL) {
            printf("%d%s", node->value, node->prev ? " " : "");
            node = node->prev;
        }
    }
    printf("\n");
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int q;
    scanf("%d", &q);

    versions[0] = NULL;
    int current_version = 0;

    for (int i = 0; i < q; i++) {
        char type;
        scanf(" %c", &type);

        if (type == '+') {
            int x;
            scanf("%d", &x);
            current_version++;
            versions[current_version] = create_node(x, versions[current_version - 1]);
        } else if (type == '-') {
            current_version++;
            if (versions[current_version - 1] != NULL) {
                versions[current_version] = versions[current_version - 1]->prev;
            }
        } else if (type == '?') {
            int v;
            scanf("%d", &v);
            print_stack(versions[v]);
        }
    }

    return 0;
}