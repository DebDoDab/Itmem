import utils
from method import Method


def lambda_splitting(_lambda, flag: bool):
    if flag:
        return _lambda / 2
    return _lambda


class GradientSplit(Method):
    def run(self):
        counter = 0
        check = False

        x0 = self.x0
        gradx0 = self.calculate_gradient(x0)
        _lambda = self._lambda

        s = _lambda * gradx0
        x = utils.lists_sub(x0, s)

        fx0 = self.func(x0)
        fx = self.func(x)

        while 2 * (fx0 - fx) < utils.vector_mod(s):
            check = True
            _lambda = lambda_splitting(_lambda, True)
            s = _lambda * gradx0
            x = utils.lists_sub(x0, s)
            fx0 = self.func(x0)
            fx = self.func(x)
        self.iterations += 1
        if check:
            check = False
            counter += 1

        while utils.vector_mod(s) >= self.eps:
            self.segments.append([x0, x])
            x0 = x
            gradx0 = self.calculate_gradient(x0)
            _lambda = lambda_splitting(_lambda, False)

            s = _lambda * gradx0
            x = utils.lists_sub(x0, s)

            fx0 = self.func(x0)
            fx = self.func(x)
            while 2 * (fx0 - fx) < utils.vector_mod(s):
                check = True
                _lambda = lambda_splitting(_lambda, True)
                s = _lambda * gradx0
                x = utils.lists_sub(x0, s)
                fx0 = self.func(x0)
                fx = self.func(x)
            self.iterations += 1
            if check:
                counter += 1
                check = False

            if counter >= 25:
                check = False
                counter = 0
                _lambda = self._lambda

        pre_result = utils.lists_sum(x, x0)
        self.answer = self.func(utils.multiply_list(pre_result, 1/2))
        self.answer_point = utils.multiply_list(pre_result, 1/2)
