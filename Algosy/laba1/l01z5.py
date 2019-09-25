inp = open("sortland.in", "r")
out = open("sortland.out", "w")

n = int(inp.readline())
a = list(map(float, inp.readline().split()))

for i in range(n):
    a[i] = (a[i], i)

for i in range(n):
    for j in range(i + 1, n):
        if a[i][0] > a[j][0]:
            a[i], a[j] = a[j], a[i]

print(a[0][1] + 1, a[n//2][1] + 1, a[n-1][1] + 1, file=out)

inp.close()
out.close()
