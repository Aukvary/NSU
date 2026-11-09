import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import poisson, expon

counts = np.random.poisson(5, size=100)

print(counts)
