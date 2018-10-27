import bisect

queries = []

with open("./haybales.in", "r") as infile:
    _ = infile.readline().split()
    haybales = infile.readline().split()
    haybales = [int(i) for i in haybales]
    for line in infile:
        queries.append(line.split())
haybales.sort()

ans = []
for query in queries:
    l = bisect.bisect_left(haybales, int(query[0]))
    r = bisect.bisect_right(haybales, int(query[1]))
    ans.append(r-l)

with open("./haybales.out", "w") as outfile:
    for i in ans:
        outfile.write(str(i)+"\n")