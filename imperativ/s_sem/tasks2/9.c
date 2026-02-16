#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL

// Расширенный алгоритм Евклида: находит (g, x, y), такие что a*x + b*y = g = gcd(a, b)
long long gcd_extended(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long g = gcd_extended(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

// Находит любое частное решение уравнения ax = b (mod M)
// Возвращает 1, если решение существует, иначе 0
int solve_linear(long long a, long long b, long long M, long long *x) {
    long long x0, y0;
    long long g = gcd_extended(a, M, &x0, &y0);
    
    if (b % g != 0) return 0; // Решения нет
    
    // Упрощаем уравнение
    long long a1 = a / g;
    long long b1 = b / g;
    long long M1 = M / g;
    
    // Теперь a1 и M1 взаимно просты, находим обратный элемент
    long long inv_x, tmp;
    gcd_extended(a1, M1, &inv_x, &tmp);
    inv_x = (inv_x % M1 + M1) % M1;
    
    // Частное решение
    *x = (b1 * inv_x) % M1;
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n, k;
    long long M;
    scanf("%d %d %lld", &n, &k, &M);

    // Расширенная матрица: k строк, n+1 столбцов
    long long A[205][205];
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j <= n; ++j) {
            scanf("%lld", &A[i][j]);
        }
    }

    int row = 0;
    int pivot_col[205];
    long long solution[205] = {0};

    for (int col = 0; col < n; ++col) {
        // Ищем строку с ненулевым элементом в текущем столбце
        int sel = -1;
        for (int i = row; i < k; ++i) {
            if (A[i][col] != 0) {
                sel = i;
                break;
            }
        }
        if (sel == -1) continue;

        // Меняем строки местами
        if (sel != row) {
            for (int j = 0; j <= n; ++j) {
                long long tmp = A[row][j];
                A[row][j] = A[sel][j];
                A[sel][j] = tmp;
            }
        }

        // Пытаемся нормализовать строку
        // Находим g = gcd(A[row][col], M)
        long long g = A[row][col];
        for (int j = col + 1; j <= n; ++j) {
            // Приводим коэффициенты по модулю g
            A[row][j] %= g;
        }
        A[row][col] = 1; // Масштабируем, оставляя 1

        // Обнуляем столбец ниже
        for (int i = row + 1; i < k; ++i) {
            if (A[i][col] != 0) {
                long long factor = A[i][col];
                for (int j = col; j <= n; ++j) {
                    A[i][j] = (A[i][j] - factor * A[row][j]) % M;
                    if (A[i][j] < 0) A[i][j] += M;
                }
            }
        }

        pivot_col[row] = col;
        ++row;
    }

    int r = row; // Ранг матрицы

    // Проверка совместности
    for (int i = r; i < k; ++i) {
        if (A[i][n] != 0) {
            printf("0\n"); // Решений нет
            return 0;
        }
    }

    // Считаем количество решений: M^(n-r) mod MOD
    long long cnt = 1;
    long long base = M % MOD;
    int exp = n - r;
    while (exp > 0) {
        if (exp & 1) cnt = (cnt * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    printf("%lld\n", cnt);

    // Обратный ход для поиска частного решения
    for (int i = r - 1; i >= 0; --i) {
        int col = pivot_col[i];
        long long sum = 0;
        for (int j = col + 1; j < n; ++j) {
            sum = (sum + A[i][j] * solution[j]) % M;
        }
        
        long long rhs = (A[i][n] - sum) % M;
        if (rhs < 0) rhs += M;
        
        // Решаем A[i][col] * solution[col] ≡ rhs (mod M)
        // Но A[i][col] может быть не взаимно прост с M
        // Используем solve_linear
        long long x;
        if (solve_linear(A[i][col], rhs, M, &x)) {
            solution[col] = x;
        } else {
            // Не должно произойти, если система совместна
            solution[col] = 0;
        }
    }

    // Выводим частное решение
    for (int i = 0; i < n; ++i) {
        printf("%lld\n", solution[i]);
    }

    return 0;
}