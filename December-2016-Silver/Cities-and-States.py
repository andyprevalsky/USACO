cs = []
with open("./citystate.in", "r") as infile:
    infile.readline()
    for line in infile:
        a, b = line.split()
        cs.append([a[0:2], b])

cities = {}
count = 0
for pair in cs:
    if pair[0] in cities and pair[1] in cities[pair[0]] and pair[0] != pair[1]:
        count += cities[pair[0]][pair[1]]
    if pair[1] in cities:
        if pair[0] in cities[pair[1]]:
            cities[pair[1]][pair[0]] += 1
        else:
            cities[pair[1]][pair[0]] = 1
    else:
        cities[pair[1]] = {pair[0]: 1}

with open("./citystate.out", "w") as outfile:
    outfile.write(str(count))