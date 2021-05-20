import utils
from method import Method


class GradientConst(Method):
    def iteration(self, x0):
        gradx0 = self.calculate_gradient(x0)
        _lambda = self.lambda_static()

        s = _lambda * gradx0
        x = utils.lists_sub(x0, s)
        self.iterations += 1
        return x, s

    def run(self):
        x0 = self.x0
        x, s = self.iteration(x0)

        while utils.vector_mod(s) >= self.eps:
            self.segments.append([x0, x])
            x0 = x
            x, s = self.iteration(x0)
            print(utils.vector_mod(utils.lists_sub(x0, x)), self.iterations)
        pre_result = utils.lists_sum(x, x0)
        self.answer = self.func(utils.multiply_list(pre_result, 1/2))
        self.answer_point = utils.multiply_list(pre_result, 1/2)
