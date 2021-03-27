from typing import Tuple
from math import sqrt
from main import f, left, right


it_count = 0
f_count = 0

phi = (1 + 5 ** 1/2)


def parabolas(
        l: float, r: float, middle: float,
        f_l: float, f_r: float, f_middle: float
) -> float:
    return middle - (
            (middle - l) ** 2 * (f_middle - f_r) -
            (middle - r) ** 2 * (f_middle - f_l)
    ) / (
                2 * ((middle - l) * (f_middle - f_r) -
                     (middle - r) * (f_middle - f_l))
        )


def iteration(l: float, r: float, eps: float, log: bool = False) -> float:
    global f_count
    global it_count
    k = (3 - sqrt(5)) / 2
    a, c = l, r
    x = (a + c) / 2
    w, v = x, x
    fx = f(x)
    f_count += 1
    fw, fv = fx, fx
    d = c - a
    e = d
    while c - a >= eps:
        prev_a = a
        prev_c = c
        it_count += 1
        check_parabola = False
        g = e
        e = d
        if x != w and x != v and w != v and fx != fw and fx != fv and fw != fv:
            arr = sorted([(x, fx), (w, fw), (v, fv)])
            l, m, r = arr[0][0], arr[1][0], arr[2][0]
            fl, fm, fr = arr[0][1], arr[1][1], arr[2][1]
            u = parabolas(l, m, r, fl, fm, fr)
            if a <= u <= c and abs(u - x) < g / 2:
                check_parabola = True
                d = abs(u - x)
        if not check_parabola:
            if x < (a + c) / 2:
                u = x + k * (c - x)
                d = c - x
            else:
                u = x - k * (x - a)
                d = x - a

        fu = f(u)
        f_count += 1
        if fu <= fx:
            if u >= x:
                a = x
            else:
                c = x
            v = w
            w = x
            x = u
            fv = fw
            fw = fx
            fx = fu
        else:
            if u >= x:
                c = u
            else:
                a = u
            if fu <= fw or w == x:
                v = w
                w = u
                fv = fw
                fw = fu
            elif fu <= fv or v == x or v == w:
                v = u
                fv = fu
        if log:
            print(f"{it_count}\t{a}\t{c}\t{(c - a) / (prev_c - prev_a)}")
    return (a + c) / 2


if __name__ == "__main__":
    for eps_power in range(0, 60, 2):
        eps = 10 ** -(eps_power / 10)
        iteration(left, right, eps)
        print(f"{eps_power / 10}\t{it_count}\t{f_count}\t")
        it_count = 0
        f_count = 0
    print("\n\n\n\n")
    print(iteration(left, right, 0.00001))
