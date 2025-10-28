from functools import wraps

def summ(v1: int | float, v2: int | float) -> int | float:
    """
        вычисляет сумму двух чисел
    """
    return v1 + v2

def sub(v1: int | float, v2: int | float) -> int | float:
    """
        вычисляет разность двух чисел
    """
    return v1 - v2

def mult(v1: int | float, v2: int | float) -> int | float:
    """
        вычисляет сумму двух чисел
    """
    return v1 * v2

def div(v1: int | float, v2: int | float) -> int | float:
    """
        вычисляет отношение двух чиселЦ
    """
    return v1 / v2

def mod(v1: int, v2: int) -> int:
    """
        вычисляет отстаток от деления v1 на v2
    """
    return v1 % v2

def pow(v: int | float, s: int | float) -> int | float:
    """
        возводит число v в степень s
    """
    return v**s

def factorial(v: int) -> int:
    """
        вычисляет факториал числа v
    """
    res = 1

    for i in range(2, v + 1):
        res *= i

    return res

def is_prime(v: int) -> bool:
    """
        определяет явялется ли число простым
    """
    return v > 1 and all(v % i != 0 for i in range(2, int(v**0.5) + 1))

def mid_val(*args) -> float:
    """
        вычисляет среднее значение из значений, переданных аргументов
    """
    return sum(args) / len(args)

def matrix(n = 0, m = 0, val = 0):
    """
        n - кол-во строк 
        m - кол-во рядов(если m = 0, то используется знчение n)
        val - знчение по умолчанию    
    """
    if m == 0:
        return [[val for _ in range(n)] for _ in range(n)]
    else:
        return [[val for _ in range(m)] for _ in range(n)]
    
def transpose(matrix: list[list]) -> list[list]:
    """
        транспонирует матрицу
    """
    return list(map(list, map(lambda *x: x, *matrix)))

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
    