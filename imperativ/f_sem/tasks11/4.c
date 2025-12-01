#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long long u64;

typedef struct {
    char name[31];
    int year;
    char country[11];
} ActorBio;

typedef struct ActorInMovie {
    char name[31];
    char movie_name[21];
    struct ActorInMovie* next;
} ActorInMovie;

u64 get_hash(char* name) {
    u64 hash = 14695981039346656037ULL;
    while (*name) {
        hash ^= (u64)(*name++);
        hash *= 1099511628211ULL;
    }
    return hash;
}

int main() {
    int n;
    int m;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &n);

    ActorBio* actors = calloc(n, sizeof(ActorBio));
    for (int i = 0; i < n; i++) {
        scanf(" \"%30[^\"]\" %d \"%10[^\"]\"", actors[i].name, &actors[i].year, actors[i].country);
    }

    scanf("%d", &m);
    ActorInMovie** movies = calloc(m, sizeof(ActorInMovie*));

    for (int i = 0; i < m; i++) {
        ActorInMovie* movie = malloc(sizeof(ActorInMovie));
        scanf(" \"%30[^\"]\" \"%20[^\"]\"", movie->name, movie->movie_name);
        movie->next = NULL;

        u64 hash = get_hash(movie->name) % m;
        int original_hash = hash;

        while (movies[hash] != NULL && strcmp(movies[hash]->name, movie->name) != 0) {
            hash = (hash + 1) % m;
        }

        if (movies[hash] == NULL) {
            movies[hash] = movie;
        } else {
            movie->next = movies[hash]->next;
            movies[hash]->next = movie;
        }
    }

    for (int i = 0; i < n; i++) {
        ActorBio bio = actors[i];

        u64 hash = get_hash(bio.name) % m;

        while (movies[hash] != NULL && strcmp(movies[hash]->name, bio.name) != 0) {
            hash = (hash + 1) % m;
        }

        if (movies[hash] != NULL && strcmp(movies[hash]->name, bio.name) == 0) {
            ActorInMovie* movie = movies[hash];
            while (movie != NULL) {
                printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", 
                       bio.name, bio.year, bio.country, bio.name, movie->movie_name);
                movie = movie->next;
            }
        }
    }

    free(actors);
    for (int i = 0; i < m; i++) {
        ActorInMovie* movie = movies[i];
        while (movie != NULL) {
            ActorInMovie* next = movie->next;
            free(movie);
            movie = next;
        }
    }
    free(movies);

    return 0;
}