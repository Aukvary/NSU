from inspect import signature
from functools import wraps

def debug_log(func):
    @wraps(func)  
    def wrapper(*args, **kwargs):
        if __debug__:
            args_list = [repr(arg) for arg in args]
            kwargs_list = [f"{name}={repr(value)}" for name, value in kwargs.items()]
            all_args = ', '.join(args_list + kwargs_list)
            
            print(f'{func.__name__}({all_args})')

        return func(*args, **kwargs)

    return wrapper

@debug_log
def sum(v1: int | float, v2: int | float) -> int | float:
    """
        вычисляет сумму двух чисел
    """
    return v1 + v2

@debug_log
def sub(v1: int | float, v2: int | float) -> int | float:
    """
        вычисляет разность двух чисел
    """
    return v1 - v2

@debug_log
def mult(v1: int | float, v2: int | float) -> int | float:
    """
        вычисляет сумму двух чисел
    """
    return v1 * v2

@debug_log
def div(v1: int | float, v2: int | float) -> int | float:
    """
        вычисляет отношение двух чиселЦ
    """
    return v1 / v2

@debug_log
def mod(v1: int, v2: int) -> int:
    """
        вычисляет отстаток от деления v1 на v2
    """
    return v1 % v2

@debug_log
def pow(v: int | float, s: int | float) -> int | float:
    """
        возводит число v в степень s
    """
    return v**s

@debug_log
def factorial(v: int) -> int:
    """
        вычисляет факториал числа v
    """
    res = 1

    for i in range(2, v + 1):
        res *= i

    return res

@debug_log
def is_prime(v: int) -> bool:
    """
        определяет явялется ли число простым
    """
    return v > 1 and all(v % i != 0 for i in range(2, int(v**0.5) + 1))

@debug_log
def mid_val(*args) -> float:
    """
        вычисляет среднее значение из значений, переданных аргументов
    """
    return sum(args) / len(args)

@debug_log
def get_matrix(iter_i, iter_j) -> list[list]:
    """
        формирует матрицу на основе двух переданных итераторов
    """
    return [[el for el in iter_j] for _ in iter_i]

@debug_log
def transpose(matrix: list[list]) -> list[list]:
    """
        транспонирует матрицу
    """
    return [list(row) for row in zip(*matrix)]

@debug_log
def get_area(mode: str, a = 0, b = 0, c = 0) -> int | float:
    """
        вычисляет площадь фигуры:
            "сircle": a - радиус
            "squre" a - сторона квадрата
            "triangle": a, b, c - стороны треугольника
            "trapezoid": a, b - основания трапеции, с - высота 
    """
    match mode:
        case "circle":
            return a * 3.14
        
        case "squre":
            return a * a
        
        case "triangle":
            p = (a + b + c) / 2
            return (p * (p - a) * (p - b) * (p - c))**0.5
        case "trapezoid":
            return (a + b) / 2 * c
    