#include <cblas.h>

void MatrixSqr(int n, const double *A, double *R) {
    // R = A * A
    // CblasRowMajor: матрицы хранятся по строкам
    // CblasNoTrans: не транспонируем A
    // alpha = 1.0, beta = 0.0 (перезаписываем R)
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                n, n, n, 1.0, A, n, A, n, 0.0, R, n);
}