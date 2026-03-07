#include <stdio.h>

void cblas_dgemm(int Layout, int TransA, int TransB,
                 int M, int N, int K,
                 double alpha, const double *A, int lda,
                 const double *B, int ldb,
                 double beta, double *C, int ldc)
{
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < K; ++k) {
                sum += A[i*lda + k] * B[k*ldb + j];
            }
            C[i*ldc + j] = alpha * sum + beta * C[i*ldc + j];
        }
    }
}