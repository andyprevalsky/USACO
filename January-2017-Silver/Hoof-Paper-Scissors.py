moves = []
import operator

with open('./hps.in', 'r') as inp:
    inp.readline()
    for line in inp:
        moves.append(line[0])

    if len(moves) == 1:
        with open("./hps.out", "w") as out:
            out.write(str(1))
        exit(1)

    left = [[0, 0] for i in range(len(moves)+1)]
    phs = [0, 0, 0]

    for i, v in enumerate(moves):
        max_index, max_value = max(enumerate(phs), key=operator.itemgetter(1))
        left[i] = [max_index, max_value]

        if v == 'P': phs[0] += 1
        elif v == 'H': phs[1] += 1
        else: phs[2] += 1
    
    max_index, max_value = max(enumerate(phs), key=operator.itemgetter(1))
    left[-1] = [max_index, max_value]

    right = [[0, 0] for i in left]
    phs = [0, 0, 0]

    for i, v in enumerate(reversed(moves)):
        index = len(right)-1-i
        max_index, max_value = max(enumerate(phs), key=operator.itemgetter(1))
        right[index] = [max_index, max_value]
        if v == 'P': phs[0] += 1
        elif v == 'H': phs[1] += 1
        else: phs[2] += 1

    max_index, max_value = max(enumerate(phs), key=operator.itemgetter(1))
    right[0] = [max_index, max_value]
    
    m = d = 0
    for i in range(1, len(left)-1):
        if left[i][1] + right[i][1] > m:
            m = left[i][1] + right[i][1]
            d = i

with open("./hps.out", "w") as out:
    out.write(str(m))

