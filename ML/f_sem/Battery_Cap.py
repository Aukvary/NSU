from Mendeleev_Table import elements

F = 96485

def split_material(mat: str):
    words = []
    i = 0
    n = len(mat)
    
    while i < n:
        if mat[i].isupper():
            j = i + 1
            while j < n and mat[j].islower():
                j += 1
            
            element = mat[i:j]
            
            k = j
            while k < n and mat[k].isdigit():
                k += 1
            if k > j:
                for a in range(int(mat[j:k])):
                    words.append(element)
            
            i = k 
        else:
            i += 1
    
    return words

def calculate_cap(mat: str):
    materials = split_material(mat)

    m = sum([elements[el] for el in materials])

    return F / (3.6 * m)    
