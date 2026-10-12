import math
import random

import matplotlib.pyplot as plt

SEED = 42
NUM_POINTS = 100_000

CENTER = 0.5
RADIUS = 0.5

MULTIPLIER = 4

def estimate_pi(num_points: int) -> tuple[list[int], list[float], list[float], int]:
    counts: list[int] = []
    errors: list[float] = []
    approx: list[float] = []
    hits = 0

    for i in range(1, num_points + 1):
        x = random.uniform(0, 1)
        y = random.uniform(0, 1)

        if (x - CENTER) ** 2 + (y - CENTER) ** 2 <= RADIUS ** 2:
            hits += 1

        current = MULTIPLIER * hits / i
        counts.append(i)
        approx.append(current)
        errors.append(abs(current - math.pi))

    return counts, errors, approx, hits


def report(counts: list[int], errors: list[float], approx: list[float],
           hits: int) -> None:
    print(f"Начальное состояние (seed): {SEED}")
    print(f"Число бросков:              {counts[-1]:,}".replace(",", " "))
    print(f"Попаданий в круг:           {hits:,}".replace(",", " "))
    print(f"Оценка π:                   {approx[-1]:.6f}")
    print(f"Истинное π (math.pi):       {math.pi:.6f}")
    print(f"Абсолютная ошибка:           {errors[-1]:.6f}")

    print()
    print(f"{'Число точек':>14} | {'Оценка π':>10} | {'Ошибка':>10}")
    print("-" * 40)
    for i in range(1, len(counts) + 1):
        if i in (10 ** k for k in range(1, 7)) or i == len(counts):
            print(
                f"{i:>14} | {approx[i - 1]:>10.5f} | {errors[i - 1]:>10.5f}"
                .replace(",", " ")
            )


def plot_error(counts: list[int], errors: list[float]) -> str:
    """Строит график ошибки от числа точек в лог-лог масштабе."""
    path = "task1_pi_error.png"

    fig, ax = plt.subplots(figsize=(9, 5.5))

    ax.plot(counts, errors, color="#1f77b4", linewidth=0.8, label="ошибка")

    ax.plot(counts, [1 / math.sqrt(n) for n in counts],
            color="#d62728", linewidth=1.2, linestyle="--",
            label=r"$\propto 1/\sqrt{N}$")

    ax.set_xscale("log")
    ax.set_yscale("log")

    ax.set_ylim(bottom=1e-4)

    ax.set_xlabel("Число использованных точек N")
    ax.set_ylabel(r"Абсолютная ошибка $|\tilde{\pi} - \pi|$")
    ax.set_title(f"Сходимость метода Монте-Карло (seed = {SEED})")
    ax.grid(True, which="both", alpha=0.3)
    ax.legend()

    fig.tight_layout()
    fig.savefig(path, dpi=150)
    plt.close(fig)
    return path


def main() -> None:
    random.seed(SEED)

    counts, errors, approx, hits = estimate_pi(NUM_POINTS)
    report(counts, errors, approx, hits)

    path = plot_error(counts, errors)
    print(f"\nГрафик сохранён в файл: {path}")


if __name__ == "__main__":
    main()
