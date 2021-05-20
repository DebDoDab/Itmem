import numpy as np
import matplotlib.pyplot as plt

from method import Method


def it_plot(its: list, n):
    x = [i for i in range(1, 200)]
    plt.plot(x, its)
    plt.show()


def plot_and_show(m: Method):
    x = np.mgrid[-20:20:150j, -20:20:150j]

    # z = x[0]**2 + 2 * x[1]**2 + 3
    z = 2 * x[0]**2 + 4 * x[1]**2 - 1 * x[0] * x[1] - 5 * x[0]

    fig, ax = plt.subplots()
    cp = ax.contour(x[0], x[1], z, levels=50)

    for p in m.segments:
        x = [p[0][0], p[1][0]]
        y = [p[0][1], p[1][1]]
        ax.plot(x, y, color='blue')

    plt.show()
