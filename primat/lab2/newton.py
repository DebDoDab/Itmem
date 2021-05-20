import numdifftools as ndt
import utils
import math
import numpy as np
from scipy.misc import derivative
from method import Method


class Newton(Method):
    def run(self):
        x0 = self.x0[:]
        gradient = self.calculate_gradient(x0)
        hessian = ndt.Hessian(self.func)(x0)
        s = np.linalg.solve(hessian, [-i for i in gradient])
        x = utils.lists_sum(x0, s)

        while utils.vector_mod(s) >= self.eps:
            self.segments.append([x0, x])
            x0 = x
            gradient = self.calculate_gradient(x0)
            hessian = ndt.Hessian(self.func)(x0)
            s = np.linalg.solve(hessian, [-i for i in gradient])
            x = utils.lists_sum(x0, s)
            self.iterations += 1

        self.answer_point = x
        self.answer = self.func(x)
