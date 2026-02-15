#include <stdio.h>

#define SIZE 100000

typedef long long i64;

typedef struct {
    i64 x;
    i64 y;
} Vec2;

Vec2 vecs[SIZE];
Vec2 hull[SIZE];
int n;

i64 orientation(Vec2 p, Vec2 q, Vec2 r) {
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

i64 dist(Vec2 p1, Vec2 p2) {
    i64 dx = p1.x - p2.x;
    i64 dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

int cmp(const void* a, const void* b) {
    if (((Vec2*)a)->x != ((Vec2*)b)->x) {
        return ((Vec2*)a)->x - ((Vec2*)b)->x;
    }
    return ((Vec2*)a)->y - ((Vec2*)b)->y;
}

int func() {
    if (n < 3) return 0;
    
    int start_idx = 0;
    for (int i = 1; i < n; i++) {
        if (vecs[i].x < vecs[start_idx].x || 
            (vecs[i].x == vecs[start_idx].x && vecs[i].y < vecs[start_idx].y)) {
            start_idx = i;
        }
    }
    
    int hull_size = 0;
    int current_idx = start_idx;
    
    do {
        hull[hull_size++] = vecs[current_idx];
        
        int next_idx = -1;
        
        for (int i = 0; i < n; i++) {
            if (i == current_idx) continue;
            
            if (next_idx == -1) {
                next_idx = i;
                continue;
            }
            
            i64 orient = orientation(vecs[current_idx], vecs[next_idx], vecs[i]);
            
            if (orient < 0) {
                next_idx = i;
            } else if (orient == 0) {
                i64 dist_to_next = dist(vecs[current_idx], vecs[next_idx]);
                i64 dist_to_i = dist(vecs[current_idx], vecs[i]);
                
                if (dist_to_i > dist_to_next) {
                    next_idx = i;
                }
            }
        }
        
        current_idx = next_idx;
        
    } while (current_idx != start_idx);
    
    return hull_size;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &vecs[i].x, &vecs[i].y);
    }
    
    int hull_size = func();
    
    printf("%d\n", hull_size);
    
    for (int i = 0; i < hull_size; i++) {
        printf("%lld %lld\n", hull[i].x, hull[i].y);
    }
    
    return 0;
}