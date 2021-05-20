import math


def vector_mod(x: list):
    return math.sqrt(sum([i ** 2 for i in x]))


def lists_sub(a: list, b: list):
    if len(a) != len(b):
        raise ArithmeticError("Lists must be same length")
    return [a[i] - b[i] for i in range(len(a))]


def lists_sum(a: list, b: list):
    if len(a) != len(b):
        raise ArithmeticError("Lists must be same length")
    return [a[i] + b[i] for i in range(len(a))]


def multiply_list(a: list, x):
    return [i * x for i in a]
