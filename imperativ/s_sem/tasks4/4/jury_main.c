#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

void MatrixSqr(int n, const double *A, double *R);

static uint32_t state[5] = {3723843285U, 3869792426U, 4214040171U, 4036220243U, 2529802169U};
static uint32_t xorwow() {
	uint32_t s, t = state[3];
	t ^= t >> 2;
	t ^= t << 1;
	state[3] = state[2]; state[2] = state[1]; state[1] = s = state[0];
	t ^= s;
	t ^= s << 4;	
	state[0] = t;
	return t + (state[4] += 362437);
}
static int myrandom(int mod) {
    return xorwow() % mod;
}

#define myassert(cond) \
    if (!(cond)) { \
        fprintf(stderr, "Test assert failed: %s\n", #cond); \
        exit(666); \
    }

int dblMatch(double val, double ref) {
    return (val - ref) <= 1e+5 * DBL_EPSILON * (fabs(ref) + 1.0);
}

int main(int argc, char **argv) {
    int n, k;
    myassert(scanf("%d", &n) == 1);
    myassert(scanf("%d", &k) == 1);

    double *A = malloc(n * n * sizeof(double));
    double *R = malloc(n * n * sizeof(double));

    if (k == 1) {
        for (int i = 0; i < n*n; i++) A[i] = 1.0;
        MatrixSqr(n, A, R);
        for (int i = 0; i < n*n; i++) myassert(dblMatch(R[i], n));
    }
    if (k == 2) {
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) A[i*n+j] = (i==j);
        MatrixSqr(n, A, R);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) myassert(dblMatch(R[i*n+j], (i==j)));
    }
    if (k == 3) {
        int ci = (int)(n * 0.795);
        int cj = (int)(n * 0.639);
        int minij = (ci < cj ? cj : cj);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) A[i*n+j] = (i<ci && j<cj) * 2.5;
        MatrixSqr(n, A, R);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) myassert(dblMatch(R[i*n+j], A[i*n+j] * 6.25 * minij));
    }
    if (k == 4 || k == 5) {
        double alpha = 2.7182818284590452353602874713527;
        double beta = 3.1415926535897932384626433832795;
        if (k == 5) { alpha = 0.12312134546367456; beta = 0.319783456345636654; }
        double sum0 = n;
        double sum1 = (n-1)*n / 2.0;
        double sum2 = (n-1)*n*(2*n-1LL) / 6.0;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) A[i*n+j] = alpha * i + beta * j;
        MatrixSqr(n, A, R);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            double chk = alpha * beta * (sum2 + i * j * sum0) + (alpha * alpha * i + beta * beta * j) * sum1;
            myassert(dblMatch(R[i*n+j], chk));
        }
    }

    fprintf(stderr, "OK\n");
    return 0;
}
