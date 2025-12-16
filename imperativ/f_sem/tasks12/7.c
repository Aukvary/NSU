#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[31];
    int year;
    char country[11];
} ActorBio;

typedef struct {
    char name[31];
    char movie_name[21];
} ActorInMovie;

typedef struct node {
    char name[31];
    
    ActorBio* bios;
    int bio_count;
    int bio_capacity;

    struct node* left;
    struct node* right;
} node;

node* create_node(const char* name) {
    node* new_node = malloc(sizeof(node));
    strcpy(new_node->name, name);
    new_node->bios = NULL;
    new_node->bio_count = 0;
    new_node->bio_capacity = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node* push(node* head, const ActorBio* bio) {
    if (head == NULL) {
        head = create_node(bio->name);
    }
    
    int cmp = strcmp(bio->name, head->name);
    
    if (cmp == 0) {
        if (head->bio_count == head->bio_capacity) {
            int new_capacity = head->bio_capacity == 0 ? 4 : head->bio_capacity * 2;
            ActorBio* temp = realloc(head->bios, new_capacity * sizeof(ActorBio));
            if (temp == NULL) {
                return head;
            }
            head->bios = temp;
            head->bio_capacity = new_capacity;
        }
        head->bios[head->bio_count] = *bio;
        head->bio_count++;
    } else if (cmp < 0) {
        head->left = push(head->left, bio);
    } else {
        head->right = push(head->right, bio);
    }
    
    return head;
}

node* search(node* head, const char* name) {
    node* current = head;
    while (current != NULL) {
        int cmp = strcmp(name, current->name);
        if (cmp == 0) {
            return current;
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

void free_tree(node* head) {
    if (head == NULL) return;
    free_tree(head->left);
    free_tree(head->right);
    if (head->bios != NULL) {
        free(head->bios);
    }
    free(head);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    int m;
    
    scanf("%d", &n);
    
    ActorBio* actors = malloc(n * sizeof(ActorBio));
    for (int i = 0; i < n; i++) {
        scanf(" \"%30[^\"]\" %d \"%10[^\"]\"", actors[i].name, &actors[i].year, actors[i].country);
    }
    
    node* head = NULL;
    for (int i = 0; i < n; i++) {
        head = push(head, &actors[i]);
    }
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        ActorInMovie movie;
        scanf(" \"%30[^\"]\" \"%20[^\"]\"", movie.name, movie.movie_name);
        
        node* found = search(head, movie.name);
        
        if (found != NULL) {
            for (int j = 0; j < found->bio_count; j++) {
                ActorBio* bio = &found->bios[j];
                printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", bio->name, bio->year, bio->country, bio->name, movie.movie_name);
            }
        }
    }
    
    free(actors);
    free_tree(head);
    
    return 0;
}