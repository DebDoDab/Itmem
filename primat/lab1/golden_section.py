from typing import Tuple
from math import sqrt
from main import f, left, right


it_count = 0
f_count = 0

phi = (1 + 5 ** 1/2)


def iteration(l: float, r: float, eps: float, log: bool = False) -> float:
    global f_count
    global it_count
    phi = (1 + sqrt(5)) / 2
    middle_left = l + (2 - phi) * (r - l)
    middle_right = r - (2 - phi) * (r - l)
    f_middle_left = f(middle_left)
    f_count += 1
    f_middle_right = f(middle_right)
    f_count += 1
    if log:
        print(f"{0}\t{l}\t{r}\t")
    while r - l >= eps:
        it_count += 1
        old_l = l
        old_r = r
        if f_middle_left < f_middle_right:
            r = middle_right
            middle_right = middle_left
            f_middle_right = f_middle_left
            middle_left = l + (2 - phi) * (r - l)
            f_middle_left = f(middle_left)
            f_count += 1
        else:
            l = middle_left
            middle_left = middle_right
            f_middle_left = f_middle_right
            middle_right = r - (2 - phi) * (r - l)
            f_middle_right = f(middle_right)
            f_count += 1
        if log:
            print(f"{it_count}\t{l}\t{r}\t{(r - l) / (old_r - old_l)}")
    return l + (r - l) / 2


if __name__ == "__main__":
    for eps_power in range(0, 60, 2):
        eps = 10 ** -(eps_power / 10)
        iteration(left, right, eps)
        print(f"{eps_power / 10}\t{it_count}\t{f_count}\t")
        it_count = 0
        f_count = 0
    print("\n\n\n\n")
    print(iteration(left, right, 0.00001))
