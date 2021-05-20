from method import Method
import utils
from scipy import optimize


class GradientFastest(Method):
    def run(self):
        x0 = self.x0
        gradx0 = self.calculate_gradient(x0)
        _lambda = self.lambda_by_fibonacci(x0)

        s = _lambda * gradx0
        x = utils.lists_sub(x0, s)
        self.iterations += 1

        while utils.vector_mod(s) >= self.eps:
            # self.segments.append([x0, x])
            x0 = x
            gradx0 = self.calculate_gradient(x0)
            _lambda = self.lambda_by_fibonacci(x0)
            s = _lambda * gradx0
            x = utils.lists_sub(x0, s)
            self.iterations += 1
        pre_result = utils.lists_sum(x, x0)
        self.answer = self.func(utils.multiply_list(pre_result, 1/2))
        self.answer_point = utils.multiply_list(pre_result, 1/2)
