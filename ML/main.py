f = lambda r, q, p, A: (((not r) or (not q)) and ((not r) or p) and (not A)) or (A and ((not p) or q) and r)

for r in range(2):
    for q in range(2):
        for p in range(2):
            if not f(r, q, p, 1):
                print('op')