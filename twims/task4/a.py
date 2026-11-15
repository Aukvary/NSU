import numpy as np


def simulate_algorithm_1(lam: float, n: int, N: int):
    p = min(lam / n, 1.0)
    trials = np.random.rand(N, n) < p
    counts = trials.sum(axis=1)

    diffs = []
    cell_indices = np.arange(1, n + 1) / n
    for i in range(N):
        if counts[i] >= 2:
            pts = cell_indices[trials[i]]
            diffs.extend(np.diff(pts))

    return counts, np.array(diffs)


def simulate_algorithm_2(lam: float, N: int):
    counts = np.random.poisson(lam, size=N)

    diffs = []
    for m in counts[2:]:
        pts = np.sort(np.random.uniform(0.0, 1.0, size=m))
        diffs.extend(np.diff(pts))

    return counts, np.array(diffs)


def simulate_algorithm_3(lam: float, N: int):
    counts = np.zeros(N, dtype=int)
    diffs = []
    w1_list = np.empty(N, dtype=float)

    for i in range(N):
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
