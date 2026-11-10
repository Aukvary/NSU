import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import poisson, expon

# ==========================================
# 1. Алгоритмы моделирования
# ==========================================


def simulate_algorithm_1(lam: float, n: int, N: int):
    """
    Первый способ: схема Бернулли на мелкой сетке из n ячеек. Возвращает:
      counts: массив числа успехов в N реализациях (длина N)
      diffs: массив всех внутренних расстояний t_{j+1} - t_j
    """
    p = min(lam / n, 1.0)
    # n независимых испытаний Бернулли для N реализаций: форма (N, n)
    trials = np.random.rand(N, n) < p
    counts = trials.sum(axis=1)

    diffs = []
    # Координаты ячеек: 1/n, 2/n, ..., 1.0
    cell_indices = np.arange(1, n + 1) / n
    for i in range(N):
        if counts[i] >= 2:
            pts = cell_indices[trials[i]]
            diffs.extend(np.diff(pts))

    return counts, np.array(diffs)


def simulate_algorithm_2(lam: float, N: int):
    """
    Второй способ: число событий по Пуассону и их равномерное размещение.
    Возвращает: counts, diffs
    """
    # 1. Число точек X ~ Poisson(lambda)
    counts = np.random.poisson(lam, size=N)

    diffs = []
    for m in counts:
        if m < 2:
            break
        # 2. m независимых равномерных точек на [0, 1], отсортированных по возрастанию
        pts = np.sort(np.random.uniform(0.0, 1.0, size=m))
        diffs.extend(np.diff(pts))

    return counts, np.array(diffs)


def simulate_algorithm_3(lam: float, N: int):
    """
    Третий способ: времена ожидания Exp(lambda).
    Возвращает: counts, diffs, w1_list (первые времена ожидания W_1)
    """
    counts = np.zeros(N, dtype=int)
    diffs = []
    w1_list = np.empty(N, dtype=float)

    for i in range(N):
        # Первое время ожидания W_1 (сохраняется всегда, даже если > 1)
        w1 = np.random.exponential(scale=1.0 / lam)
        w1_list[i] = w1

        pts = []
        current_time = w1
        while current_time <= 1.0:
            pts.append(current_time)
            w = np.random.exponential(scale=1.0 / lam)
            current_time += w

        m = len(pts)
        counts[i] = m
        if m >= 2:
            diffs.extend(np.diff(pts))

    return counts, np.array(diffs), w1_list


#
#
# # ==========================================
# # 2. Эксперимент 1: Влияние шага сетки n
# #    Фиксированы lambda = 5, N = 10 000, n in [10, 50, 200]
# # ==========================================
#
# lam = 5.0
# N = 10_000
# n_values = [10, 50, 200]
#
# # Моделирование алгоритмов 2 и 3 (не зависят от n)
# counts_2, diffs_2 = simulate_algorithm_2(lam, N)
# counts_3, diffs_3, w1_3 = simulate_algorithm_3(lam, N)
#
# # Моделирование алгоритма 1 для разных n
# results_1 = {n: simulate_algorithm_1(lam, n, N) for n in n_values}
#
# # --- График 1: Распределение числа событий N(1) ---
# fig, axes = plt.subplots(1, 3, figsize=(18, 5), sharey=True)
# k_max = int(lam + 4 * np.sqrt(lam) + 2)
# k_range = np.arange(0, k_max + 1)
# poiss_pmf = poisson.pmf(k_range, mu=lam)
#
# for idx, n in enumerate(n_values):
#     ax = axes[idx]
#     counts_1, _ = results_1[n]
#
#     bins = np.arange(-0.5, k_max + 1.5, 1.0)
#     # Гистограммы относительных частот
#     ax.hist(
#         counts_1,
#         bins=bins,
#         density=True,
#         alpha=0.4,
#         color="royalblue",
#         label=f"Алогритм 1 (Бернулли, n={n})",
#         edgecolor="blue",
#     )
#     ax.hist(
#         counts_2,
#         bins=bins,
#         density=True,
#         alpha=0.3,
#         color="forestgreen",
#         label="Алгоритм 2 (Равномерный)",
#         edgecolor="green",
#     )
#     ax.hist(
#         counts_3,
#         bins=bins,
#         density=True,
#         alpha=0.2,
#         color="orange",
#         label="Алгоритм 3 (Exp интервалы)",
#         edgecolor="darkorange",
#     )
#
#     # Теоретическая кривая Пуассона
#     ax.plot(k_range, poiss_pmf, "r.--", lw=2, ms=8, label=r"Теория: $\Pi_\lambda$")
#
#     ax.set_title(rf"Число событий: $n = {n}$, $\lambda = {lam}$")
#     ax.set_xlabel("Число событий $k$")
#     if idx == 0:
#         ax.set_ylabel("Относительная частота")
#     ax.grid(True, alpha=0.3)
#     ax.legend(fontsize=8)
#
# plt.suptitle(
#     r"Эксперимент 1: Сходимость распределения числа событий при росте $n$ ($N = 10\,000$)",
#     fontsize=14,
# )
# plt.tight_layout()
# plt.show()
#
# # --- График 2: Распределения расстояний между точками внутри [0, 1] ---
# fig, axes = plt.subplots(1, 3, figsize=(18, 5), sharey=True)
# dist_bins = np.linspace(0, 0.7, 36)
#
# for idx, n in enumerate(n_values):
#     ax = axes[idx]
#     _, diffs_1 = results_1[n]
#
#     # Нормированные гистограммы внутренних расстояний
#     ax.hist(
#         diffs_1,
#         bins=dist_bins,
#         density=True,
#         alpha=0.4,
#         color="royalblue",
#         label=f"Алогритм 1 (n={n})",
#         edgecolor="blue",
#     )
#     ax.hist(
#         diffs_2,
#         bins=dist_bins,
#         density=True,
#         alpha=0.3,
#         color="forestgreen",
#         label="Алгоритм 2",
#         edgecolor="green",
#     )
#     ax.hist(
#         diffs_3,
#         bins=dist_bins,
#         density=True,
#         alpha=0.2,
#         color="orange",
#         label="Алгоритм 3",
#         edgecolor="darkorange",
#     )
#
#     ax.set_title(rf"Внутренние расстояния: $n = {n}$, $\lambda = {lam}$")
#     ax.set_xlabel("Расстояние $t_{j+1} - t_j$")
#     if idx == 0:
#         ax.set_ylabel("Плотность $h$")
#     ax.grid(True, alpha=0.3)
#     ax.legend(fontsize=8)
#
# plt.suptitle(
#     "Эксперимент 1: Сглаживание гистограммы расстояний при росте $n$", fontsize=14
# )
# plt.tight_layout()
# plt.show()
#
#
# # ==========================================
# # 3. Эксперимент 2: Влияние числа повторений N
# #    Фиксированы lambda = 5, n = 10, N in [100, 1 000, 10 000]
# # ==========================================
#
# N_values = [100, 1_000, 10_000]
# fig, axes = plt.subplots(1, 3, figsize=(18, 5), sharey=True)
#
# for idx, n_reps in enumerate(N_values):
#     ax = axes[idx]
#     c_1, _ = simulate_algorithm_1(lam=5.0, n=10, N=n_reps)
#     c_2, _ = simulate_algorithm_2(lam=5.0, N=n_reps)
#
#     bins = np.arange(-0.5, 15.5, 1.0)
#     ax.hist(
#         c_1,
#         bins=bins,
#         density=True,
#         alpha=0.5,
#         color="crimson",
#         label="Алгоритм 1 (n=10)",
#         edgecolor="black",
#     )
#     ax.plot(k_range, poiss_pmf, "b.--", lw=2, ms=8, label=r"Теория: $\Pi_5$")
#
#     ax.set_title(f"$N = {n_reps}$ повторений ($n = 10$)")
#     ax.set_xlabel("Число событий $k$")
#     if idx == 0:
#         ax.set_ylabel("Относительная частота")
#     ax.set_xlim(-0.5, 14.5)
#     ax.grid(True, alpha=0.3)
#     ax.legend(fontsize=9)
#
# plt.suptitle(
#     "Эксперимент 2: Влияние числа реализаций $N$ при грубой сетке $n = 10$", fontsize=14
# )
# plt.tight_layout()
# plt.show()
#
#
# # ==========================================
# # 4. Дополнительное исследование:
# #    Первые времена ожидания W_1 vs внутренние расстояния
# # ==========================================
#
# fig, ax = plt.subplots(figsize=(9, 5))
# t_vals = np.linspace(0, 1.0, 200)
# exp_pdf = lam * np.exp(-lam * t_vals)
#
# bins_comp = np.linspace(0, 1.0, 41)
# ax.hist(
#     w1_3,
#     bins=bins_comp,
#     density=True,
#     alpha=0.5,
#     color="skyblue",
#     edgecolor="navy",
#     label="Первые времена $W_1$ (Алгоритм 3)",
# )
# ax.hist(
#     diffs_3,
#     bins=bins_comp,
#     density=True,
#     alpha=0.4,
#     color="orange",
#     edgecolor="darkorange",
#     label="Внутренние расстояния на [0, 1]",
# )
# ax.plot(
#     t_vals, exp_pdf, "r-", lw=2.5, label=r"Теор. плотность $\lambda e^{-\lambda t}$"
# )
#
# ax.set_title(
#     r"Дополнительное исследование: выборка $W_1$ против внутренних расстояний ($\lambda = 5$)"
# )
# ax.set_xlabel("Длительность $t$")
# ax.set_ylabel("Плотность")
# ax.set_xlim(0, 1.0)
# ax.grid(True, alpha=0.3)
# ax.legend(fontsize=10)
#
# plt.tight_layout()
# plt.show()
