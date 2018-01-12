def triangles():
    a = [1]
    yield a
    a=[1,1]
    yield a
    for i in range(3, 11):
        b = [1]
        for j in range(2, i):
            x = a[j - 2] + a[j-1]
            b.append(x)
        b.append(1)
        yield b
        a = b



n = 0
results = []
for t in triangles():
    print(t)
    results.append(t)
    n = n + 1
    if n == 10:
        break



