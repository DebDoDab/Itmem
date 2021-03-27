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
    n = 0
    while ((r - l) / eps) > get_fibonacci_number(n + 2):
        n += 1
    middle_left = l + get_fibonacci_number(n) / get_fibonacci_number(n + 2) * (r - l)
    middle_right = l + get_fibonacci_number(n + 1) / get_fibonacci_number(n + 2) * (r - l)
    f_middle_left = f(middle_left)
    f_count += 1
    f_middle_right = f(middle_right)
    f_count += 1
    if log:
        print(f"{0}\t{l}\t{r}\t")
    if f_middle_left > f_middle_right:
        l = middle_left
        temp_point = middle_right
        f_temp_point = f_middle_right
    else:
        r = middle_right
        temp_point = middle_left
        f_temp_point = f_middle_left
    while r - l >= eps:
        it_count += 1
        old_l = l
        old_r = r
        if temp_point - l < r - temp_point:
            middle_left = temp_point
            f_middle_left = f_temp_point
            middle_right = r - (middle_left - l)
            f_middle_right = f(middle_right)
            f_count += 1
        else:
            middle_right = temp_point
            f_middle_right = f_temp_point
            middle_left = l + (r - middle_left)
            f_middle_left = f(middle_left)
            f_count += 1

        if f_middle_left > f_middle_right:
            l = middle_left
            temp_point = middle_right
            f_temp_point = f_middle_right
        else:
            r = middle_right
            temp_point = middle_left
            f_temp_point = f_middle_left
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
