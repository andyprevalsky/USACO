cows = []

with open('./bphoto.in', 'r') as inp:
    inp.readline()
    for d, line in enumerate(inp):
        cows.append([d, int(line)])

cows.sort(key=lambda k: k[1])
for i in range(len(cows)):
    cows[i][1] = i+1
cows.sort(key=lambda k: k[0])

BITa = [0 for i in range(len(cows)+1)]
BITb = [0 for i in BITa]
left = [0 for i in cows]
right = [0 for i in cows]

def update(bit, index, val):
    while (index < len(BITa)):
        bit[index] += val
        index += index & -index

def getSum(bit, index):
    res = 0
    while (index > 0):
        res += bit[index]
        index -= index & -index
    return res

for i, v in enumerate(cows):
    left[i] += (i - getSum(BITa, v[1]))
    update(BITa, v[1], 1)

for i, v in enumerate(reversed(cows)):
    right[len(right)-1-i] += (i - getSum(BITb, v[1]))
    update(BITb, v[1], 1)

total = 0
for i in range(len(left)):
    if max([left[i], right[i]]) > (2*min([left[i], right[i]])):
        total += 1

with open("./bphoto.out", "w") as out:
    out.write(str(total))