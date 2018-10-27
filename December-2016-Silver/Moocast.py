cows = []
with open("./moocast.in", "r") as infile:
    infile.readline()
    for line in infile:
        cows.append([int(i) for i in line.split()])

class Node:
    def __init__(self, visited=False, next=None):
        self.visited = visited
        self.next = []

nodes = [Node() for i in range(len(cows))]

for i, v in enumerate(cows):
    for i2, v2 in enumerate(cows):
        if i == i2: continue
        if (v2[1]-v[1])**2 + (v2[0]-v[0])**2 <= v[2]**2:
            nodes[i].next.append(nodes[i2])

maxSum = 0
def dfs(node):
    global maxSum
    count = 1
    if node.visited: return 0
    node.visited = True
    for node in node.next:
        count += dfs(node)
    if count > maxSum: maxSum = count
    return count

for node in nodes:
    for n2 in nodes:
        n2.visited = False    
    dfs(node)

with open("./moocast.out", "w") as outfile:
    outfile.write(str(maxSum))