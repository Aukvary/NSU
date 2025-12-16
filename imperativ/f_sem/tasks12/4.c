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

int cmp_bio(const void* a, const void* b) {
    ActorBio* bio_a = (ActorBio*)a;
    ActorBio* bio_b = (ActorBio*)b;
    return strcmp(bio_a->name, bio_b->name);
}

int cmp_movie(const void* a, const void* b) {
    ActorInMovie* movie_a = (ActorInMovie*)a;
    ActorInMovie* movie_b = (ActorInMovie*)b;
    return strcmp(movie_a->name, movie_b->name);
}

int binary_search(ActorInMovie* movies, int m, const char* name) {
    int l = 0;
    int r = m - 1;
    int res = -1;
    
    while (l <= r) {
        int m = l + (r - l) / 2;
        int cmp = strcmp(movies[m].name, name);
        
        if (cmp == 0) {
            res = m;
            r = m - 1;
        } else if (cmp < 0) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    int m;
    
    scanf("%d", &n);
    
    ActorBio* actors = calloc(n, sizeof(ActorBio));
    for (int i = 0; i < n; i++) {
        scanf(" \"%30[^\"]\" %d \"%10[^\"]\"", actors[i].name, &actors[i].year, actors[i].country);
    }
    
    scanf("%d", &m);
    ActorInMovie* movies = calloc(m, sizeof(ActorInMovie));
    for (int i = 0; i < m; i++) {
        scanf(" \"%30[^\"]\" \"%20[^\"]\"", 
              movies[i].name, movies[i].movie_name);
    }
    
    qsort(actors, n, sizeof(ActorBio), cmp_bio);
    qsort(movies, m, sizeof(ActorInMovie), cmp_movie);
    
    for (int i = 0; i < n; i++) {
        ActorBio* bio = &actors[i];
        
        int idx = binary_search(movies, m, bio->name);
        
        while (idx >= 0 && idx < m && strcmp(movies[idx].name, bio->name) == 0) {
            printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", bio->name, bio->year, bio->country, bio->name, movies[idx].movie_name);
            idx++;
        }
    }
    
    free(actors);
    free(movies);
    
    return 0;
}