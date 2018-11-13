cows = []
with open("./moocast.in", "r") as infile:
    infile.readline()
    for line in infile:
        cows.append([int(i) for i in line.split()])

edges = []
for i1, v1 in enumerate(cows):
    for i2, v2 in enumerate(cows[i1+1:]):
        edges.append([(v1[0]-v2[0])**2 + (v1[1]-v2[1])**2, i1, i2+i1+1])
edges.sort(key=lambda k: k[0])

idCount = 0
ids = [i for i in range(len(cows))]

def isConnected():
    global ids
    for i in range(len(ids)):
        if i == 0: continue
        if ids[i-1] != ids[i]: return False
    return True

count = 0
for edge in edges:
    if isConnected(): break
    if ids[edge[1]] != ids[edge[2]]:
        count = edge[0]
        orig = ids[edge[1]]
        for i, id in enumerate(ids):
            if id == orig: ids[i] = ids[edge[2]]

with open("./moocast.out", "w") as outfile:
    outfile.write(str(count))