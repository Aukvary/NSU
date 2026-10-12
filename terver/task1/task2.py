import math
import random
from collections import deque

import matplotlib.pyplot as plt

SEED = 42

WIDTH = 30
HEIGHT = 30

NUM_EXPERIMENTS = 1000

P_MIN = 0.30
P_MAX = 0.90
P_STEP = 0.02

# Доверительный интервал для доли: коэффициент 1.96 для уровня 95 %.
Z_SCORE = 1.96

# Смещения соседей по стороне: диагональные переходы запрещены.
NEIGHBORS = ((-1, 0), (1, 0), (0, -1), (0, 1))


def generate_field(p: float) -> list[list[bool]]:
    """Генерирует поле HEIGHT x WIDTH, где каждая клетка проходима с вероятностью p."""
    return [[random.random() < p for _ in range(WIDTH)] for _ in range(HEIGHT)]


def has_percolation(field: list[list[bool]]) -> bool:
    """Проверяет наличие пути из верхнего ряда в нижний по проходимым клеткам.

    Обход в ширину стартует сразу из всех проходимых клеток верхнего ряда:
    начальная и конечная клетки могут быть любыми.
    """
    height = len(field)
    width = len(field[0])

    queue: deque[tuple[int, int]] = deque()
    visited = [bytearray(width) for _ in range(height)]

    for col in range(width):
        if field[0][col]:
            visited[0][col] = 1
            queue.append((0, col))

    while queue:
        row, col = queue.popleft()

        if row == height - 1:
            return True

        for d_row, d_col in NEIGHBORS:
            next_row = row + d_row
            next_col = col + d_col
            if not 0 <= next_row < height or not 0 <= next_col < width:
                continue
            if visited[next_row][next_col] or not field[next_row][next_col]:
                continue
            visited[next_row][next_col] = 1
            queue.append((next_row, next_col))

    return False


def estimate_percolation(p: float) -> tuple[int, float]:
    """Проводит NUM_EXPERIMENTS полей с вероятностью проходимости p.

    Возвращает число успешных экспериментов и оценку вероятности перколяции.
    """
    successes = 0

    for _ in range(NUM_EXPERIMENTS):
        if has_percolation(generate_field(p)):
            successes += 1

    return successes, successes / NUM_EXPERIMENTS


def confidence_interval(prob: float) -> float:
    """Полуширина 95 % доверительного интервала для оценки вероятности."""
    return Z_SCORE * math.sqrt(prob * (1.0 - prob) / NUM_EXPERIMENTS)


def sweep_p() -> tuple[list[float], list[float], list[int]]:
    """Считает вероятность перколяции для всех значений p из P_MIN до P_MAX."""
    steps = round((P_MAX - P_MIN) / P_STEP) + 1
    p_values = [round(P_MIN + i * P_STEP, 10) for i in range(steps)]

    probabilities: list[float] = []
    successes: list[int] = []

    for p in p_values:
        hits, prob = estimate_percolation(p)
        probabilities.append(prob)
        successes.append(hits)

    return p_values, probabilities, successes


def report(p_values: list[float], probabilities: list[float], successes: list[int]) -> None:
    print(f"Начальное состояние (seed):     {SEED}")
    print(f"Размер поля:                    {WIDTH} x {HEIGHT} клеток")
    print(f"Экспериментов на одно p:        {NUM_EXPERIMENTS}")
    print(f"Значений p:                     {len(p_values)} "
          f"(от {p_values[0]:.2f} до {p_values[-1]:.2f} с шагом {P_STEP})")

    mid = len(p_values) // 2
    print(f"При p = {p_values[mid]:.2f}: оценка вероятности перколяции "
          f"{probabilities[mid]:.3f} (успешных экспериментов: {successes[mid]})")
    print(f"При p = {p_values[-1]:.2f}: оценка вероятности перколяции "
          f"{probabilities[-1]:.3f} (успешных экспериментов: {successes[-1]})")


def plot_probability(p_values: list[float], probabilities: list[float]) -> str:
    """Строит график вероятности перколяции в зависимости от вероятности проходимости."""
    path = "task2_percolation.png"

    errors = [confidence_interval(prob) for prob in probabilities]

    fig, ax = plt.subplots(figsize=(9, 5.5))

    ax.errorbar(
        p_values,
        probabilities,
        yerr=errors,
        fmt="-o",
        markersize=4,
        linewidth=1.2,
        capsize=3,
        color="#1f77b4",
        ecolor="#7f7f7f",
        label="оценка по Монте-Карло",
    )

    ax.set_xlim(P_MIN - P_STEP, P_MAX + P_STEP)
    ax.set_ylim(-0.03, 1.03)

    ax.set_xlabel("Вероятность проходимости клетки p")
    ax.set_ylabel(r"Вероятность перколяции $\hat{P}$")
    ax.set_title(
        f"Перколяция сверху вниз: поле {WIDTH}x{HEIGHT}, "
        f"{NUM_EXPERIMENTS} экспериментов (seed = {SEED})"
    )
    ax.grid(True, alpha=0.3)
    ax.legend()

    fig.tight_layout()
    fig.savefig(path, dpi=150)
    plt.close(fig)
    return path


def main() -> None:
    random.seed(SEED)

    p_values, probabilities, successes = sweep_p()
    report(p_values, probabilities, successes)

    path = plot_probability(p_values, probabilities)
    print(f"\nГрафик сохранён в файл: {path}")


if __name__ == "__main__":
    main()
