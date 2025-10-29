from fnmatch import fnmatch


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

def symbols() -> str:
    """
        возвращает строку, в которой содержаться все специальные символы
    """
    return '-+,.;%!@#$%^&*()_={}[]"\'№:?/<>`~'

def is_russian_phone_number(s: str) -> bool:
    """

    """
    my_s = s.replace(' ', '')
    return fnmatch(my_s, '+7??????????') or fnmatch(my_s, '8??????????')
    

def anagrams(s1: str, s2: str) -> bool:
    """
        определяет являются ли строки анограмами 
    """
    return len(set(s1 + s2)) == len(s1)