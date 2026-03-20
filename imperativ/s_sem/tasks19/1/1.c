#include <stdio.h>
#include <stdlib.h>

#define SIZE 1005

char maze[SIZE][SIZE];
int visited[SIZE][SIZE];
int n;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void fill(int r, int c) {
    int* queue_r = malloc(SIZE * SIZE * sizeof(int));
    int* queue_c = malloc(SIZE * SIZE * sizeof(int));
    int head = 0, tail = 0;

    queue_r[tail] = r;
    queue_c[tail] = c;
    tail++;
    visited[r][c] = 1;

    while (head < tail) {
        int curr_r = queue_r[head];
        int curr_c = queue_c[head];
        head++;

        for (int i = 0; i < 4; i++) {
            int nr = curr_r + dx[i];
            int nc = curr_c + dy[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < n && 
                maze[nr][nc] == ' ' && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                queue_r[tail] = nr;
                queue_c[tail] = nc;
                tail++;
            }
        }
    }
    free(queue_r);
    free(queue_c);
}

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d", &n);
    fgetc(stdin); 

    int start_c = -1;
    for (int i = 0; i < n; i++) {
        fgets(maze[i], SIZE + 2, stdin);
        if (i != 0) continue;
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == ' ') {
                start_c = j;
                break;
            }        
        }
    }

    if (start_c != -1) {
        fill(0, start_c);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == ' ' && !visited[i][j]) {
                count++;
                fill(i, j);
            }
        }
    }

    printf("%d\n", count);
    return 0;
}