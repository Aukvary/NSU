#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double x;
    double y;
} vec2;

double angle(vec2* v1, vec2* v2) {
    double dot = v1->x * v2->x + v1->y * v2->y;
    double cross = v1->x * v2->y - v1->y * v2->x;
    
    return atan2(fabs(cross), dot);
}

double rad2deg(double radians) {
    return radians * 180.0 / PI;
}

int main() {
    double x1, y1, x2, y2, x3, y3;
    int n;
    FILE* in = fopen("input.txt", "r");
    fscanf(in, "%d", &n);
    
    for (int i = 0; i < n; i++) {
        fscanf(in, "%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);

        vec2 AB = { x2 - x1, y2 - y1 };
        vec2 AC = { x3 - x1, y3 - y1 };
        
        printf("%0.20g\n", rad2deg(angle(&AB, &AC)));
    }
    
    return 0;
}