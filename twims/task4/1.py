from a import simulate_algorithm_1, simulate_algorithm_2, simulate_algorithm_3

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import poisson

lam = 5.0
N = 10_000
n_values = [10, 50, 200]

# Моделирование алгоритмов 2 и 3 (не зависят от n)
counts_2, diffs_2 = simulate_algorithm_2(lam, N)
counts_3, diffs_3, w1_3 = simulate_algorithm_3(lam, N)

# Моделирование алгоритма 1 для разных n
results_1 = {n: simulate_algorithm_1(lam, n, N) for n in n_values}

# --- График 1: Распределение числа событий N(1) ---
fig, axes = plt.subplots(1, 3, figsize=(18, 5), sharey=True)
k_max = int(lam + 4 * np.sqrt(lam) + 2)
k_range = np.arange(0, k_max + 1)
poiss_pmf = poisson.pmf(k_range, mu=lam)

for idx, n in enumerate(n_values):
    ax = axes[idx]
    counts_1, _ = results_1[n]

    bins = np.arange(-0.5, k_max + 1.5, 1.0)
    # Гистограммы относительных частот
    ax.hist(
        counts_1,
        bins=bins,
        density=True,
        alpha=0.4,
        color="royalblue",
        label=f"Алгоритм 1 (Бернулли, n={n})",
        edgecolor="blue",
    )
    ax.hist(
        counts_2,
        bins=bins,
        density=True,
        alpha=0.3,
        color="forestgreen",
        label="Алгоритм 2 (Равномерный)",
        edgecolor="green",
    )
    ax.hist(
        counts_3,
        bins=bins,
        density=True,
        alpha=0.2,
        color="orange",
        label="Алгоритм 3 (Exp интервалы)",
        edgecolor="darkorange",
    )

    # Теоретическая кривая Пуассона
    ax.plot(k_range, poiss_pmf, "r.--", lw=2, ms=8, label=r"Теория: $\Pi_\lambda$")

    ax.set_title(rf"Число событий: $n = {n}$, $\lambda = {lam}$")
    ax.set_xlabel("Число событий $k$")
    if idx == 0:
        ax.set_ylabel("Относительная частота")
    ax.grid(True, alpha=0.3)
    ax.legend(fontsize=8)

plt.suptitle(
    r"Эксперимент 1: Сходимость распределения числа событий при росте $n$ ($N = 10\,000$)",
    fontsize=14,
)
plt.tight_layout()
plt.show()

# --- График 2: Распределения расстояний между точками внутри [0, 1] ---
fig, axes = plt.subplots(1, 3, figsize=(18, 5), sharey=True)
dist_bins = np.linspace(0, 0.7, 36)

for idx, n in enumerate(n_values):
    ax = axes[idx]
    _, diffs_1 = results_1[n]

    # Нормированные гистограммы внутренних расстояний
    ax.hist(
        diffs_1,
        bins=dist_bins,
        density=True,
        alpha=0.4,
        color="royalblue",
        label=f"Алгоритм 1 (n={n})",
        edgecolor="blue",
    )
    ax.hist(
        diffs_2,
        bins=dist_bins,
        density=True,
        alpha=0.3,
        color="forestgreen",
        label="Алгоритм 2",
        edgecolor="green",
    )
    ax.hist(
        diffs_3,
        bins=dist_bins,
        density=True,
        alpha=0.2,
        color="orange",
        label="Алгоритм 3",
        edgecolor="darkorange",
    )

    ax.set_title(rf"Внутренние расстояния: $n = {n}$, $\lambda = {lam}$")
    ax.set_xlabel("Расстояние $t_{j+1} - t_j$")
    if idx == 0:
        ax.set_ylabel("Плотность $h$")
    ax.grid(True, alpha=0.3)
    ax.legend(fontsize=8)

plt.suptitle(
    "Эксперимент 1: Сглаживание гистограммы расстояний при росте $n$", fontsize=14
)
plt.tight_layout()
plt.show()
