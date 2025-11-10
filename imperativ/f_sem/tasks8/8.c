#include <stdio.h>
#include <stdlib.h>

typedef enum {
    EMPTY = 0,
    DOWN = 1,
    UP = 2,
    LEFT = 4,
    RIGHT = 8
} directions;

// Функция для получения количества частиц в ячейке
int count_particles(int cell) {
    int count = 0;
    if (cell & RIGHT) count++;
    if (cell & LEFT) count++;
    if (cell & UP) count++;
    if (cell & DOWN) count++;
    return count;
}

// Функция для обработки столкновений
int handle_collision(int cell) {
    int count = count_particles(cell);
    
    // Если ровно 2 частицы - поворачиваем на 90 градусов
    if (count == 2) {
        // Получаем направления частиц
        int dir1 = -1, dir2 = -1;
        
        if (cell & RIGHT) {
            if (dir1 == -1) dir1 = RIGHT;
            else dir2 = RIGHT;
        }
        if (cell & LEFT) {
            if (dir1 == -1) dir1 = LEFT;
            else dir2 = LEFT;
        }
        if (cell & UP) {
            if (dir1 == -1) dir1 = UP;
            else dir2 = UP;
        }
        if (cell & DOWN) {
            if (dir1 == -1) dir1 = DOWN;
            else dir2 = DOWN;
        }
        
        // Поворот на 90 градусов для конкретных пар
        // В примере: (RIGHT, LEFT) -> (UP, DOWN)
        if ((dir1 == RIGHT && dir2 == LEFT) || (dir1 == LEFT && dir2 == RIGHT)) {
            return UP | DOWN;
        }
        if ((dir1 == UP && dir2 == DOWN) || (dir1 == DOWN && dir2 == UP)) {
            return LEFT | RIGHT;
        }
        // Для диагональных пар: (RIGHT, UP) -> (UP, LEFT) и т.д.
        if ((dir1 == RIGHT && dir2 == UP) || (dir1 == UP && dir2 == RIGHT)) {
            return UP | LEFT;
        }
        if ((dir1 == RIGHT && dir2 == DOWN) || (dir1 == DOWN && dir2 == RIGHT)) {
            return DOWN | LEFT;
        }
        if ((dir1 == LEFT && dir2 == UP) || (dir1 == UP && dir2 == LEFT)) {
            return UP | RIGHT;
        }
        if ((dir1 == LEFT && dir2 == DOWN) || (dir1 == DOWN && dir2 == LEFT)) {
            return DOWN | RIGHT;
        }
    }
    
    // Для 1, 3 или 4 частиц - направления сохраняются
    return cell;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    if (in == NULL) {
        printf("Error opening input file\n");
        return 1;
    }
    
    int N, M, T;
    fscanf(in, "%d %d %d", &N, &M, &T);
    
    // Выделяем память для текущего и следующего состояния
    int **grid = (int**)malloc(N * sizeof(int*));
    int **new_grid = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        grid[i] = (int*)malloc(M * sizeof(int));
        new_grid[i] = (int*)malloc(M * sizeof(int));
    }
    
    // Читаем начальное состояние
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            unsigned int temp;
            fscanf(in, "%x", &temp);
            grid[i][j] = (int)temp;
        }
    }
    fclose(in);
    
    // Моделируем T шагов
    for (int step = 0; step < T; step++) {
        // Инициализируем новую решетку как пустую
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                new_grid[i][j] = EMPTY;
            }
        }
        
        // Фаза перемещения
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int cell = grid[i][j];
                
                // Перемещаем частицы согласно их направлениям
                if (cell & RIGHT) {
                    int new_j = (j + 1) % M;
                    new_grid[i][new_j] |= RIGHT;
                }
                if (cell & LEFT) {
                    int new_j = (j - 1 + M) % M;
                    new_grid[i][new_j] |= LEFT;
                }
                if (cell & UP) {
                    int new_i = (i - 1 + N) % N;
                    new_grid[new_i][j] |= UP;
                }
                if (cell & DOWN) {
                    int new_i = (i + 1) % N;
                    new_grid[new_i][j] |= DOWN;
                }
            }
        }
        
        // Фаза столкновений
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                new_grid[i][j] = handle_collision(new_grid[i][j]);
            }
        }
        
        // Обновляем grid для следующего шага
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                grid[i][j] = new_grid[i][j];
            }
        }
    }
    
    // Выводим результат
    FILE *out = fopen("output.txt", "w");
    if (out == NULL) {
        printf("Error opening output file\n");
        return 1;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fprintf(out, "%X", grid[i][j]);
            if (j < M - 1) fprintf(out, " ");
        }
        fprintf(out, "\n");
    }
    fclose(out);
    
    // Освобождаем память
    for (int i = 0; i < N; i++) {
        free(grid[i]);
        free(new_grid[i]);
    }
    free(grid);
    free(new_grid);
    
    return 0;
}