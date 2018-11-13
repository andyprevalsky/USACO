spotted = []
normal = []

with open("cownomics.in", "r") as infile:
    n, m = infile.readline().split()
    n = int(n)
    m = int(m)
    for i in range(n):
        spotted.append(infile.readline())
    for i in range(n):
        normal.append(infile.readline())

total = 0

for i in range(m-2):
    for j in range(i+1, m-1):
        for k in range(j+1, m):
            substrings = set()
            for x in range(n):
                substrings.add(spotted[x][i] + spotted[x][j] + spotted[x][k])
            for x in range(n):
                if (normal[x][i] + normal[x][j] + normal[x][k]) in substrings: break
                if x == n-1: total += 1

with open("cownomics.out", "w") as outfile:
    outfile.write(str(total))