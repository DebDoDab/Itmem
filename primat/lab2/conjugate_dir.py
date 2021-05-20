from method import Method
from scipy import optimize
import utils


class ConjugateDir(Method):
    def run(self):
        p = [[1, 0], [0, 1]]
        cur_x = self.x0[:]
        prev_x = cur_x[:]
        while self.len_vector(p[1]) >= self.eps:
            new_function = lambda l: self.func([cur_x[k] + l * p[1][k] for k in range(len(cur_x))])
            h_min = optimize.minimize(new_function, x0=0)["x"][0]
            cur_x = [cur_x[k] + h_min * p[1][k] for k in range(len(cur_x))]
            self.segments.append([prev_x, cur_x])
            prev_x = cur_x[:]
            y = cur_x[:]
            i = 0
            while i <= 1:
                new_function = lambda l: self.func([cur_x[k] + l * p[i][k] for k in range(len(cur_x))])
                h_min = optimize.minimize(new_function, x0=0)["x"][0]
                cur_x = [cur_x[k] + h_min * p[i][k] for k in range(len(cur_x))]
                i += 1
            i = 0
            self.iterations += 1
            p[i] = p[i+1][:]
            p[1] = [cur_x[k] - y[k] for k in range(len(p))]
        self.answer_point = cur_x
