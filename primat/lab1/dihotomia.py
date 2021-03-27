from typing import Tuple

from main import f, left, right


it_count = 0
f_count = 0


def iteration(l: float, r: float, eps: float) -> Tuple[float, float]:
    global f_count
    middle_left = (l + r) / 2. - eps / 4
    middle_right = (l + r) / 2. + eps / 4
    f_middle_left = f(middle_left)
    f_count += 1
    f_middle_right = f(middle_right)
    f_count += 1
    # print(l, r)
    if f_middle_left < f_middle_right:
        r = middle_right
    elif f_middle_left > f_middle_right:
        l = middle_left
    else:
        l = middle_left
        r = middle_right
    # print(l, r)
    return l, r


def find_min(eps: float, log: bool = False) -> float:
    l = left
    r = right
    it = 0

    if log:
        print(f"{l}\t{r}")
    while r - l >= eps:
        new_l, new_r = iteration(l, r, eps)
        it += 1
        if log:
            print(f"{new_l}\t{new_r}\t{(new_r - new_l) / (r - l)}")
        l = new_l
        r = new_r

    global it_count
    it_count = it

    return (r + l) / 2


if __name__ == "__main__":
    for eps_power in range(0, 60, 2):
        eps = 10 ** -(eps_power / 10)
        find_min(eps)
        print(f"{eps_power / 10}\t{it_count}\t{f_count}\t")
        it_count = 0
        f_count = 0
    print("\n\n\n\n")
    print(find_min(0.00001))
