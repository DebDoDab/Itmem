with open("aplusb.in", "r") as inp:
    with open("aplusb.out", "w") as out:
            print(sum(list(map(int, inp.readline().split()))), file=out)
