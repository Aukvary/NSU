#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x;
    long long y;
    long long dist;
} Point;

int cmp(const void *a, const void *b) {
    return ((Point*)a)->dist - ((Point*)b)->dist;
}

int main() {
    int k;
    scanf("%d", &k);

    Point *pts = NULL;
    int n = 0;
    int size = 0;
    long long x, y;

    while (scanf("%lld %lld", &x, &y) != EOF) {
        if (n == size) {
            size = size ? size * 2 : 8;
            pts = realloc(pts, size * sizeof(Point));
        }
        pts[n].x = x;
        pts[n].y = y;
        pts[n].dist = x * x + y * y;
        n++;
    }

    qsort(pts, n, sizeof(Point), cmp);

    if (k > n) k = n;

    for (int i = 0; i < k; i++) {
        printf("%lld %lld\n", pts[i].x, pts[i].y);
    }

    free(pts);
    return 0;
}