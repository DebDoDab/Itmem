from operator import itemgetter
with open("race.in", "r") as inp:
    with open("race.out", "w") as out:
        n = int(inp.readline())
        a = []
        for i in range(n):
            country, name = inp.readline().split()
            a.append((country, i, name))
        a.sort()
        lastcountry = ""
        for i in range(n):
            if lastcountry != a[i][0]:
                print(f"=== {a[i][0]} ===", file=out)
                lastcountry = a[i][0]
            print(a[i][2], file=out)
