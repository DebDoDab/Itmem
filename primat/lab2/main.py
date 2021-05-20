from gradient_const import GradientConst
from gradient_split import GradientSplit
from gradient_fastest import GradientFastest
from conjugate_dir import ConjugateDir
from conjugate_grad import ConjugateGrad
from newton import Newton
from plot import plot_and_show, it_plot
import random


def generate_func(k: int, n: int):
    a = [1]
    for i in range(n - 2):
        a.append(random.randint(1, k))
    a.append(k)
    # print(a)

    def funct(x: list):
        for i in range(n):
            return x[i]**2 * a[i]
    return funct


def func(x: list) -> float:
    # return x[0]**2 + x[1]**2 + 3  # [12, -3]
    # return 2 * x[0]**2 + 4 * x[1]**2 - 1 * x[0] * x[1] - 5 * x[0]  # [-3, 5]
    # return -3 * x[0]**2 + x[1]**2 + 7 * x[0] * x[1] - 3 * x[1] + 9  # [12, 9]
    # ans = 100 * x[0] + x[1]
    # return ans
    pass


n = 100
iterations = []
for k in range(1, 200):
    f = generate_func(k, n)
    rand_point = [random.randint(-10, 10) for i in range(n)]
    method = GradientFastest(f, 0.001, n, 0.5, rand_point)
    method.run()
    iterations.append(method.iterations)
    # print('steps: ', method.iterations)

it_plot(iterations, n)
# print("segments: ", method.segments)
# print("answer: ", method.answer)
# print("answer point: ", method.answer_point)
# plot_and_show(method)
