#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOTAL 100005

int n;
char *lines[MAX_TOTAL];
int lens[MAX_TOTAL];
int offsets[MAX_TOTAL];
int word_starts[MAX_TOTAL];
int w_cnt = 0;

int dist[MAX_TOTAL];
int edge_from[MAX_TOTAL];
char edge_char[MAX_TOTAL];

typedef struct {
    int r, c;
} Pos;

Pos queue[MAX_TOTAL];

int get_idx(int r, int c) {
    return offsets[r] + (c - 1);
}

void get_rc(int idx, int *r, int *c) {
    int left = 1, right = n;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (offsets[mid] <= idx) {
            *r = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    *c = idx - offsets[*r] + 1;
}

void precompute_words() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < lens[i]; j++) {
            if (lines[i][j] >= 'a' && lines[i][j] <= 'z') {
                if (j == 0 || lines[i][j - 1] == '.') {
                    word_starts[w_cnt++] = get_idx(i, j + 1);
                }
            }
        }
    }
}

void solve() {
    int r1, c1, r2, c2;
    if (scanf("%d %d %d %d", &r1, &c1, &r2, &c2) != 4) return;
    int start = get_idx(r1, c1);
    int target = get_idx(r2, c2);

    for (int i = 0; i < offsets[n + 1]; i++) dist[i] = -1;

    int head = 0, tail = 0;
    dist[start] = 0;
    queue[tail++] = (Pos){r1, c1};

    while (head < tail) {
        Pos curr = queue[head++];
        int u = get_idx(curr.r, curr.c);
        if (u == target) break;

        int nr, nc;

        nc = curr.c - 1;
        if (nc >= 1) {
            int v = get_idx(curr.r, nc);
            if (dist[v] == -1) { dist[v] = dist[u] + 1; edge_from[v] = u; edge_char[v] = 'h'; queue[tail++] = (Pos){curr.r, nc}; }
        }

        nc = curr.c + 1;
        if (nc <= lens[curr.r]) {
            int v = get_idx(curr.r, nc);
            if (dist[v] == -1) { dist[v] = dist[u] + 1; edge_from[v] = u; edge_char[v] = 'l'; queue[tail++] = (Pos){curr.r, nc}; }
        }

        if (curr.r > 1) {
            nr = curr.r - 1;
            nc = (curr.c < lens[nr]) ? curr.c : lens[nr];
            int v = get_idx(nr, nc);
            if (dist[v] == -1) { dist[v] = dist[u] + 1; edge_from[v] = u; edge_char[v] = 'k'; queue[tail++] = (Pos){nr, nc}; }
        }

        if (curr.r < n) {
            nr = curr.r + 1;
            nc = (curr.c < lens[nr]) ? curr.c : lens[nr];
            int v = get_idx(nr, nc);
            if (dist[v] == -1) { dist[v] = dist[u] + 1; edge_from[v] = u; edge_char[v] = 'j'; queue[tail++] = (Pos){nr, nc}; }
        }

        int v0 = get_idx(curr.r, 1);
        if (dist[v0] == -1) { dist[v0] = dist[u] + 1; edge_from[v0] = u; edge_char[v0] = '0'; queue[tail++] = (Pos){curr.r, 1}; }

        int v_end = get_idx(curr.r, lens[curr.r]);
        if (dist[v_end] == -1) { dist[v_end] = dist[u] + 1; edge_from[v_end] = u; edge_char[v_end] = '$'; queue[tail++] = (Pos){curr.r, lens[curr.r]}; }

        int low = 0, high = w_cnt - 1, res = -1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (word_starts[mid] > u) { res = word_starts[mid]; high = mid - 1; }
            else low = mid + 1;
        }
        if (res != -1 && dist[res] == -1) {
            dist[res] = dist[u] + 1; edge_from[res] = u; edge_char[res] = 'w';
            int tr, tc; get_rc(res, &tr, &tc);
            queue[tail++] = (Pos){tr, tc};
        }

        low = 0, high = w_cnt - 1, res = -1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (word_starts[mid] < u) { res = word_starts[mid]; low = mid + 1; }
            else high = mid - 1;
        }
        if (res != -1 && dist[res] == -1) {
            dist[res] = dist[u] + 1; edge_from[res] = u; edge_char[res] = 'b';
            int tr, tc; get_rc(res, &tr, &tc);
            queue[tail++] = (Pos){tr, tc};
        }
    }

    static char path[MAX_TOTAL];
    int path_ptr = 0;
    int curr_v = target;
    while (curr_v != start) {
        path[path_ptr++] = edge_char[curr_v];
        curr_v = edge_from[curr_v];
    }
    for (int i = path_ptr - 1; i >= 0; i--) putchar(path[i]);
    putchar('\n');
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    int total_offset = 0;
    for (int i = 1; i <= n; i++) {
        char buf[MAX_TOTAL];
        scanf("%s", buf);
        lens[i] = strlen(buf);
        lines[i] = strdup(buf);
        offsets[i] = total_offset;
        total_offset += lens[i];
    }
    offsets[n + 1] = total_offset;

    precompute_words();

    int q;
    scanf("%d", &q);
    while (q--) {
        solve();
    }
    return 0;
}