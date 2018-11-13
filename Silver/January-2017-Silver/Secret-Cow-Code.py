import math

with open('./cowcode.in', 'r') as inp:
    s, index = inp.readline().split()
    index = int(index) - 1

def getPrev(index, length):
    if index < len(s):
        return s[index]
    if index < (length // 2):
        return getPrev(index, length // 2)
    if index == (length // 2):
        return getPrev(length//2 - 1, length//2)
    return getPrev(index - (length//2 + 1), length//2)

numRotations = math.ceil(math.log(index/len(s), 2))
with open("./cowcode.out", "w") as out:
    out.write(str(getPrev(index, 2**(numRotations)*len(s))))
