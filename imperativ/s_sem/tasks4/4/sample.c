#include <assert.h>
void MatrixSqr(int n, const double *A, double *R);
int main() {
    double A[3][3] = {{0,1,2},{2,0,0},{3,0,1}};
    double R[3][3];
    MatrixSqr(3, &A[0][0], &R[0][0]);
    assert(R[0][0] == 8 && R[0][1] == 0 && R[0][2] == 2);
    assert(R[1][0] == 0 && R[1][1] == 2 && R[1][2] == 4);
    assert(R[2][0] == 3 && R[2][1] == 3 && R[2][2] == 7);
    return 0;
}
