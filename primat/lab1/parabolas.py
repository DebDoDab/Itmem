from typing import Tuple
from math import sqrt
from main import f, left, right


it_count = 0
f_count = 0


def get_fibonacci_number(n: int) -> float:
    return (1 / sqrt(5)) * (((1 + sqrt(5)) / 2) ** n - ((1 - sqrt(5)) / 2) ** n)


def iteration(l: float, r: float, eps: float, log: bool = False) -> float:
    global f_count
    global it_count
    middle = (l + r) / 2
    f_middle = f(middle)
    f_count += 1
    f_r = f(r)
    f_count += 1
    f_l = f(l)
    f_count += 1
    if log:
        print(f"{0}\t{l}\t{r}\t")
    while r - l >= eps:
        it_count += 1
        old_l = l
        old_r = r
        u = middle - (
                (middle - l) ** 2 * (f_middle - f_r) -
                (middle - r) ** 2 * (f_middle - f_l)
        ) / (
                2 * ((middle - l) * (f_middle - f_r) -
                     (middle - r) * (f_middle - f_l))
        )
        if u > r or u < l:
            print(it_count, l, r, u)
            raise ValueError("Wrong segment")
        f_u = f(u)
        f_count += 1

        middle_left = middle
        f_middle_left = f_middle
        middle_right = u
        f_middle_right = f_u
        if middle_left > middle_right:
            middle_left, middle_right = middle_right, middle_left
            f_middle_left, f_middle_right = f_middle_right, f_middle_left

        if f_middle_left < f_middle_right:
            r = middle_right
            f_r = f_middle_right
            middle = middle_left
            f_middle = f_middle_left
        elif f_middle_left > f_middle_right:
            l = middle_left
            f_l = f_middle_left
            middle = middle_right
            f_middle = f_middle_right
        else:
            l = middle_left
            f_l = f_middle_left
            r = middle_right
            f_r = f_middle_right
            middle = (l + r) / 2
            f_middle = f(middle)
            f_count += 1

        if log:
            print(f"{it_count}\t{l}\t{r}\t{(r - l) / (old_r - old_l)}")
    return l + (r - l) / 2


if __name__ == "__main__":
    for eps_power in range(0, 60, 2):
        eps = 10 ** -(eps_power / 10)
        iteration(-2, 2, eps)
        print(f"{eps_power / 10}\t{it_count}\t{f_count}\t")
        it_count = 0
        f_count = 0
    print("\n\n\n\n")
    print(iteration(-2, 2, 0.00001))
