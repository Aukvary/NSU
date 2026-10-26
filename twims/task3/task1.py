import numpy as np

SEED = 42
N = 10_000
B = 1_000
ALPHA = 0.05


def mad(x: np.ndarray) -> float:
    med = np.median(x)
    return float(np.median(np.abs(x - med)))


def bootstrap_ci(
    x: np.ndarray,
    statistic,
    n_boot: int = B,
    alpha: float = ALPHA,
) -> tuple[float, float]:
    n = len(x)
    rng = np.random.default_rng(SEED)
    stats = np.empty(n_boot)
    for b in range(n_boot):
        idx = rng.integers(0, n, size=n)
        stats[b] = statistic(x[idx])
    lo = np.quantile(stats, alpha / 2)
    hi = np.quantile(stats, 1 - alpha / 2)
    return float(lo), float(hi)


def report(mad_point, var_point, mad_ci, var_ci) -> None:
    print("Выборка: Exponential(scale=1), n = 10 000, B = 1 000, уровень 95%")
    print()

    (mad_lo, mad_hi), (var_lo, var_hi) = mad_ci, var_ci

    print("MAD:")
    print(f"  оценка:      {mad_point:.4f}")
    print(
        f"  95% ДИ:      [{mad_lo:.4f}; {mad_hi:.4f}]  (ширина {mad_hi - mad_lo:.4f})"
    )
    print()

    print("Дисперсия:")
    print(f"  оценка:      {var_point:.4f}")
    print(
        f"  95% ДИ:      [{var_lo:.4f}; {var_hi:.4f}]  (ширина {var_hi - var_lo:.4f})"
    )
    print()

    mad_rel = (mad_hi - mad_lo) / mad_point
    var_rel = (var_hi - var_lo) / var_point

    print("Сравнение:")
    print("-" * 52)
    print("MAD измеряется в единицах исходных данных, а дисперсия")
    print("— в их квадрате, поэтому ширины интервалов напрямую")
    print("сравнивать нельзя. Честная мера — относительная ширина")
    print("(ширина ДИ / точечная оценка):")
    print()
    print(f"  отн. ширина ДИ MAD:         {mad_rel:.2%}")
    print(f"  отн. ширина ДИ дисперсии:   {var_rel:.2%}")
    print()
    print("Вывод: оба интервала дают сопоставимую относительную")
    print("неопределённость; разброс оценивается с точностью порядка")
    print(f"{max(mad_rel, var_rel):.0%}. MAD устойчивее к выбросам, чем дисперсия.")


def main() -> None:
    rng = np.random.default_rng(SEED)
    x = rng.exponential(scale=1.0, size=N)

    mad_point = mad(x)
    var_point = float(np.var(x))

    mad_ci = bootstrap_ci(x, mad)
    var_ci = bootstrap_ci(x, np.var)

    report(mad_point, var_point, mad_ci, var_ci)


if __name__ == "__main__":
    main()
