from Mendeleev_Table import list_elements, elements

nums = '123456789'
F = 96485

def split_material(mat: str):
    words = []
    i = 0
    n = len(mat)
    
    while i < n:
        # Находим начало элемента (заглавная буква)
        if mat[i].isupper():
            # Находим конец элемента (строчные буквы)
            j = i + 1
            while j < n and mat[j].islower():
                j += 1
            
            element = mat[i:j]
            
            # Находим число после элемента
            k = j
            while k < n and mat[k].isdigit():
                k += 1
            
            count = int(mat[j:k]) if j < k else 1
            words.extend([element] * count)
            
            i = k  # Переходим к следующему элементу
        else:
            i += 1
    
    return words

def calculate_cap(mat: str):
    materials = split_material(mat)

    z = sum([list_elements[el] for el in materials])
    m = sum([elements[el] for el in materials])

    return (z * F) / (3.6 * m)    
