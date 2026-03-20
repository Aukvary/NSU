#include <stdio.h>
#include <stdlib.h>

#define SIZE 105

typedef struct {
    int r;
    int c;
} Vec2;

int m, n;
char maze[SIZE][SIZE];
int dist[SIZE][SIZE];

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &m, &n);

    Vec2 start;
    Vec2 finish;

    for (int i = 0; i < m; i++) {
        scanf("%s", maze[i]);
        for (int j = 0; j < n; j++) {
            dist[i][j] = -1; 
            if (maze[i][j] == 'S') {
                start.r = i;
                start.c = j;
            } else if (maze[i][j] == 'F') {
                finish.r = i;
                finish.c = j;
            }
        }
    }

    Vec2 queue[SIZE * SIZE];
    int head = 0, tail = 0;

    queue[tail++] = start;
    dist[start.r][start.c] = 0;

    int found = 0;
    while (head < tail) {
        Vec2 curr = queue[head++];

        if (curr.r == finish.r && curr.c == finish.c) {
            printf("%d\n", dist[curr.r][curr.c]);
            found = 1;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            if (maze[nr][nc] == 'X') continue;
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[curr.r][curr.c] + 1;
            queue[tail++] = (Vec2){nr, nc};
        }
    }

    if (!found) {
        printf("-1\n");
    }

    return 0;
}