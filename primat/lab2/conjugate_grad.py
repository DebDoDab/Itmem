from method import Method
import numdifftools as ndt


class ConjugateGrad(Method):
    def run(self):
        k = 0
        pk = ndt.Gradient(self.func)(self.x0)
        cur_x = self.x0[:]
        prev_x = cur_x[:]

        while True:
            tmp = cur_x[:]
            cur_x = [cur_x[i] - self.lambda_by_golden_section(self.x0)*pk[i] for i in range(len(cur_x))]
            self.segments.append([prev_x, cur_x])
            prev_x = cur_x[:]
            gr = ndt.Gradient(self.func)(cur_x)

            if self.len_vector(gr) < self.eps:
                break

            if k + 1 == self.n:
                self.x0 = cur_x[:]
                k = 0
                pk = ndt.Gradient(self.func)(self.x0)
                continue

            b = ((self.len_vector(ndt.Gradient(self.func)(cur_x)) ** 2) /
                 (self.len_vector(ndt.Gradient(self.func)(tmp)) ** 2))
            pk = [-gr[i] - b*pk[i] for i in range(len(pk))]
            self.iterations += 1
        self.answer = cur_x
        self.answer_point = self.func(cur_x)
        return self.answer
