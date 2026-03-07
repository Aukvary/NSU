#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double c0, c1, c2, c3;
    double l
} CPol;

typedef struct {
    double l, r;
    CPol x, y, z;
} Row;

double polynomial_value(CPol *p, double t) {
    double u = t - p->l;
    return p->c0 + p->c1 * u + p->c2 * u * u + p->c3 * u * u * u;
}

double polynomial_derivative(CPol *p, double t) {
    double u = t - p->l;
    return p->c1 + 2.0 * p->c2 * u + 3.0 * p->c3 * u * u;
}

double integrand(Row *span, double t) {
    double dx = polynomial_derivative(&(span->x), t);
    double dy = polynomial_derivative(&(span->y), t);
    double dz = polynomial_derivative(&(span->z), t);
    
    return sqrt(dx*dx + dy*dy + dz*dz);
}

double simpson(Row *span, double a, double b, int n) {
    if (n % 2 != 0) n++;
    
    double h = (b - a) / n;
    double sum = integrand(span, a) + integrand(span, b);
    
    for (int i = 1; i < n; i += 2) {
        sum += 4.0 * integrand(span, a + i * h);
    }
    
    for (int i = 2; i < n; i += 2) {
        sum += 2.0 * integrand(span, a + i * h);
    }
    
    return sum * h / 3.0;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    
    Row *spans = malloc(n * sizeof(Row));
    
    for (int i = 0; i < n; i++) {
        double l, r;
        double c0, c1, c2, c3;
        

        scanf("%lf %lf", &l, &r);
        spans[i].l = l;
        spans[i].r = r;
        

        scanf("%lf %lf %lf %lf", &c0, &c1, &c2, &c3);
        spans[i].x = (CPol){c0, c1, c2, c3, l};
        

        scanf("%lf %lf %lf %lf", &c0, &c1, &c2, &c3);
        spans[i].y = (CPol){c0, c1, c2, c3, l};
        

        scanf("%lf %lf %lf %lf", &c0, &c1, &c2, &c3);
        spans[i].z = (CPol){c0, c1, c2, c3, l};
    }
    
    double len = 0.0;
    
    for (int i = 0; i < n; i++) {
        Row *span = &spans[i];
        double a = span->l;
        double b = span->r;
        


        double length = b - a;
        int n = (int)(length * 1000); 
        if (n < 100) n = 100; 
        if (n > 10000) n = 10000; 
        
        len += simpson(span, a, b, n);
    }
    
    printf("%.9f\n", len);
    
    free(spans);
    
    return 0;
}