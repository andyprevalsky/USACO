moves = []
import operator

with open('./hps.in', 'r') as inp:
    _, c = inp.readline().split()
    c = int(c)
    for line in inp:
        moves.append(line[0])

cuts = []
total = 0


def getCuts(array):
    global c, total, cuts
    if len(cuts) == c:
        return

    left = [[0] for i in range(len(array)+1)]
    phs = [0, 0, 0]

    for i, v in enumerate(moves):
        if i in cuts:
            phs = [0, 0, 0]
        else:
            left[i] = [j for j in phs]
        if v == 'P': phs[0] += 1
        elif v == 'H': phs[1] += 1
        else: phs[2] += 1

    if len(left)-1 not in cuts:
        left[-1] = phs


    right = [[0] for i in left]
    phs = [0, 0, 0]

    for i, v in enumerate(reversed(moves)):
        index = len(right)-1-i

        if index in cuts:
            phs = [0, 0, 0]
        else:
            right[index] = [j for j in phs]
        if v == 'P': phs[0] += 1
        elif v == 'H': phs[1] += 1
        else: phs[2] += 1

    if 0 not in cuts:
        right[0] = phs
    
    biggestPartition = float('-inf')
    cutIndex = 0
    same = set()
    for i in range(1, len(left)-1):
        for d, j in enumerate(left[i]):
            for d2, k in enumerate(right[i]):
                if d2 == d: continue
                if j + k > biggestPartition:
                    biggestPartition = j + k
                    cutIndex = i
                    same = set([i])
                elif j + k == biggestPartition: 
                    same.add(i)

    cuts.append(cutIndex)  
    getCuts(array)

    if len(same) == 1: return biggestPartition
    else: 
        print("SAME", biggestPartition)
        exit()
        return max([getCuts(i) for i in same])
    
        
getCuts(moves)
cuts.sort()
s = 0
final = []    
for i in cuts:
    final.append(moves[s:i])
    s = i
final.append(moves[s:])

total = 0
for j in final:
    total += max([j.count('P'), j.count('H'), j.count('S')])

with open("./hps.out", "w") as out:
    out.write(str(total))
