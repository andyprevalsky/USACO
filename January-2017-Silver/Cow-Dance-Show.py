import heapq
cowDuration = []

with open("./cowdance.in", "r") as infile:
    _, Tmax = infile.readline().split()
    Tmax = int(Tmax)
    for line in infile:
        cowDuration.append(int(line))

def getTime(stageSize):
    h = []
    for i in range(stageSize):
        heapq.heappush(h, cowDuration[i])

    delay = 0
    n = len(cowDuration)
    while (stageSize != n):
        nextCow = heapq.heappop(h)
        orig = nextCow
        delay += (nextCow-delay)
        count = 0
        while (nextCow == orig and nextCow):
            count += 1
            nextCow = heapq.heappop(h)
        heapq.heappush(h, nextCow)
        for i in range(count):
            heapq.heappush(h, cowDuration[stageSize]+delay)
            stageSize += 1
            if stageSize == n: break

    return max(h)

l = len(cowDuration)
r = 1

while l != r+1:
    mid = (l+r)//2
    time = getTime(mid)
    if time == Tmax:
        with open("./cowdance.out", "w") as outfile:
            outfile.write(str(mid))
            exit()
    elif time < Tmax:
        l = mid
    else:
        r = mid

if mid > time:
    res = r
else:
    res = l

with open("./cowdance.out", "w") as outfile:
    outfile.write(str(res))