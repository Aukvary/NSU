from a import simulate_algorithm_3

import numpy as np
import matplotlib.pyplot as plt

lam = 5.0
N = 10_000

fig, ax = plt.subplots(figsize=(9, 5))
t_vals = np.linspace(0, 1.0, 200)
exp_pdf = lam * np.exp(-lam * t_vals)

counts_3, diffs_3, w1_3 = simulate_algorithm_3(lam, N)

bins_comp = np.linspace(0, 1.0, 41)
ax.hist(
    w1_3,
    bins=bins_comp,
    density=True,
    alpha=0.5,
    color="skyblue",
    edgecolor="navy",
    label="Первые времена $W_1$ (Алгоритм 3)",
)
ax.hist(
    diffs_3,
    bins=bins_comp,
    density=True,
    alpha=0.4,
    color="orange",
    edgecolor="darkorange",
    label="Внутренние расстояния на [0, 1]",
)
ax.plot(
    t_vals, exp_pdf, "r-", lw=2.5, label=r"Теор. плотность $\lambda e^{-\lambda t}$"
)

ax.set_title(
    r"Дополнительное исследование: выборка $W_1$ против внутренних расстояний ($\lambda = 5$)"
)
ax.set_xlabel("Длительность $t$")
ax.set_ylabel("Плотность")
ax.set_xlim(0, 1.0)
ax.grid(True, alpha=0.3)
ax.legend(fontsize=10)

plt.tight_layout()
plt.show()
