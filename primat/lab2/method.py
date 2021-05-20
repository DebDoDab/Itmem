from numdifftools import Gradient
import math


class Method:
    def __init__(self, func, eps, n, _lambda, x0: list):
        self.func = func
        self.eps = eps
        self.x0 = x0
        self.n = n
        self._lambda = _lambda
        self.iterations = 0
        self.function_calls = 0
        self.answer = None
        self.answer_point = None
        self.relations = []
        self.range = []
        self.segments = []

    def run(self):
        raise NotImplementedError()

    @classmethod
    def len_vector(cls, x: list):
        return sum([i ** 2 for i in x]) ** 0.5

    def calculate_gradient(self, x: list):
        return Gradient(self.func)(x)

    def lambda_static(self):
        return self._lambda

    def lambda_by_golden_section(self, x: list):
        a = 0
        b = 10
        gr = self.calculate_gradient(x)

        k1 = (3 - math.sqrt(5)) / 2
        k2 = (math.sqrt(5) - 1) / 2

        p1 = a + k1 * (b - a)
        p2 = a + k2 * (b - a)

        f1 = self.func([x[i] - gr[i] * p1 for i in range(len(gr))])
        f2 = self.func([x[i] - gr[i] * p2 for i in range(len(gr))])
        while True:
            if f1 < f2:
                b = p2
                p2 = p1
                f2 = f1
                p1 = a + k1 * (b - a)
                f1 = self.func([x[i] - gr[i] * p1 for i in range(len(gr))])
            else:
                a = p1
                p1 = p2
                f1 = f2
                p2 = a + k2 * (b - a)
                f2 = self.func([x[i] - gr[i] * p2 for i in range(len(gr))])
            if b - a < self.eps:
                return (a + b) / 2

    def lambda_by_fibonacci(self, x: list):
        a = 0
        b = 1

        def fib(x):
            return int(1 / math.sqrt(5) * (((1 + math.sqrt(5)) / 2) ** x - ((1 - math.sqrt(5)) / 2) ** x))

        fn_2 = (b - a) / self.eps
        n = 1
        while fib(n) <= fn_2:
            n += 1
        n -= 2

        gr = self.calculate_gradient(x)

        p1 = a + fib(n) / fib(n + 2) * (b - a)
        p2 = a + fib(n + 1) / fib(n + 2) * (b - a)

        f1 = self.func([x[i] - gr[i] * p1 for i in range(len(gr))])
        f2 = self.func([x[i] - gr[i] * p2 for i in range(len(gr))])

        k = 0
        while k < n:
            k += 1
            if f1 <= f2:
                b = p2
                p2 = p1
                p1 = b + a - p2
                f2 = f1
                f1 = self.func([x[i] - gr[i] * p1 for i in range(len(gr))])
            else:
                a = p1
                p1 = p2
                p2 = b + a - p1
                f1 = f2
                f2 = self.func([x[i] - gr[i] * p2 for i in range(len(gr))])
        return (a + b) / 2
