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

int main() {
    int n;
    int m;
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    scanf("%d", &n);
    
    ActorBio* actors = calloc(n, sizeof(ActorBio));
    for (int i = 0; i < n; i++) {
        scanf(" \"%30[^\"]\" %d \"%10[^\"]\"", 
              actors[i].name, &actors[i].year, actors[i].country);
    }
    
    scanf("%d", &m);
    ActorInMovie* movies = calloc(m, sizeof(ActorInMovie));
    for (int i = 0; i < m; i++) {
        scanf(" \"%30[^\"]\" \"%20[^\"]\"", movies[i].name, movies[i].movie_name);
    }
    
    qsort(actors, n, sizeof(ActorBio), cmp_bio);
    qsort(movies, m, sizeof(ActorInMovie), cmp_movie);
    
    int i = 0;
    int j = 0;
    
    while (i < n && j < m) {
        int cmp = strcmp(actors[i].name, movies[j].name);
        
        if (cmp < 0) {
            i++;
        } else if (cmp > 0) {
            j++;
        } else {
            int start_i = i;
            int start_j = j;
            
            while (i < n && strcmp(actors[start_i].name, actors[i].name) == 0) {
                i++;
            }
            
            while (j < m && strcmp(movies[start_j].name, movies[j].name) == 0) {
                j++;
            }
            
            for (int k = start_i; k < i; k++) {
                for (int l = start_j; l < j; l++) {
                    printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                           actors[k].name, actors[k].year, actors[k].country,
                           actors[k].name, movies[l].movie_name);
                }
            }
        }
    }
    
    free(actors);
    free(movies);
    
    return 0;
}