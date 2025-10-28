
glasnii = "aeiouAEIOU"
soglasnii = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"



def my_reverse(s: str) -> str:
    """
        переворачивает строку
    """
    return s[::-1]

def is_palidrom(s: str) -> bool:
    """
        определяет является ли строка полидромом 
    """
    return s == s[::-1]

def gl_count(s: str) -> int:
    """
        определяет кол-во гласных букв
    """
    return sum(1 for c in s if c in glasnii)

def sgl_count(s: str) -> int:
    """
        определяет кол-во гласных букв
    """
    return sum(1 for c in s if c in soglasnii)

def anagrams(s1: str, s2: str) -> bool:
    """
        определяет являются ли строки анограмами 
    """
    return len(set(s1 + s2)) == len(s1)