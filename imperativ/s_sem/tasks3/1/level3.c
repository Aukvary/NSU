#include "myblas.h"

void dgemm(int m, int n, int k, double alpha, const double *A, const double *B,
           double beta, double *C) {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      C[i * n + j] *= beta;
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      double sum = 0.0;
      for (int p = 0; p < k; ++p) {
        sum += A[i * k + p] * B[p * n + j];
      }
      C[i * n + j] += alpha * sum;
    }
  }
}