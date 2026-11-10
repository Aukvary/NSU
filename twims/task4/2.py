from a import simulate_algorithm_1, simulate_algorithm_2

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import poisson

lam = 5.0
N_values = [100, 1_000, 10_000]

fig, axes = plt.subplots(1, 3, figsize=(18, 5), sharey=True)
k_max = int(lam + 4 * np.sqrt(lam) + 2)
k_range = np.arange(0, k_max + 1)
poiss_pmf = poisson.pmf(k_range, mu=lam)

for idx, n_reps in enumerate(N_values):
    ax = axes[idx]
    c_1, _ = simulate_algorithm_1(lam=5.0, n=10, N=n_reps)
    c_2, _ = simulate_algorithm_2(lam=5.0, N=n_reps)

    bins = np.arange(-0.5, 15.5, 1.0)
    ax.hist(
        c_1,
        bins=bins,
        density=True,
        alpha=0.5,
        color="crimson",
        label="Алгоритм 1 (n=10)",
        edgecolor="black",
    )
    ax.plot(k_range, poiss_pmf, "b.--", lw=2, ms=8, label=r"Теория: $\Pi_5$")

    ax.set_title(f"$N = {n_reps}$ повторений ($n = 10$)")
    ax.set_xlabel("Число событий $k$")
    if idx == 0:
        ax.set_ylabel("Относительная частота")
    ax.set_xlim(-0.5, 14.5)
    ax.grid(True, alpha=0.3)
    ax.legend(fontsize=9)

plt.suptitle(
    "Эксперимент 2: Влияние числа реализаций $N$ при грубой сетке $n = 10$", fontsize=14
)
plt.tight_layout()
plt.show()
