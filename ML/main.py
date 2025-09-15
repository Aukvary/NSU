def f(num):
    if 1 <= num <= 3: print("I" * num)
    elif num == 4: print("IV")
    elif 5 <= num <= 8: print("V" + "I" * (num - 5))
    elif num == 9: print("IX")
    elif num == 10: print("X")
    else: print("ошибка")

for i in range(-1, 12):
    f(i)