#

def SortCharacters(s):
    order = [0] * len(s)
    count = {'$': 0, "A": 0, 'C': 0, 'G': 0, 'T': 0}
    for char in s:
        count[char] += 1
    symb = ['$', 'A', 'C', 'G', 'T']
    for i in range(1, 5):
        count[symb[i]] += count[symb[i-1]]
    for j in range(len(s) - 1, -1, -1):
        c = s[j]
        count[c] -= 1
        order[count[c]] = j
    return order


def ComputeCharClasses(s, order):
    class_chars = [0] * len(s)
    for i in range(1, len(s)):
        if s[order[i]] == s[order[i-1]]:
            class_chars[order[i]] = class_chars[order[i-1]]
        else:
            class_chars[order[i]] = class_chars[order[i-1]] + 1
    return class_chars


def SortDoubled(s, L, old_order, old_class):
    count = [0] * len(s)
    new_order = [0] * len(s)
    for i in range(len(s)):
        count[old_class[i]] += 1
    for i in range(1, len(s)):
        count[i] += count[i-1]
    for j in range(len(s) - 1, -1, -1):
        start = (old_order[j] - L + len(s)) % len(s)
        cl = old_class[start]
        count[cl] -= 1
        new_order[count[cl]] = start
    return new_order


def UpdateClasses(new_order, old_class, L):
    n = len(new_order)
    new_class = [0] * n
    for i in range(1, n):
        cur = new_order[i]
        mid = (cur + L) % n
        prev = new_order[i-1]
        mid_prev = (prev + L) % n
        if old_class[cur] == old_class[prev] and old_class[mid] == old_class[mid_prev]:
            new_class[cur] = new_class[prev]
        else:
            new_class[cur] = new_class[prev] + 1
    return new_class


def BuildSuffixArray(S):
    order = SortCharacters(S)
    class_ = ComputeCharClasses(S, order)
    L = 1
    while L < len(S):
        order = SortDoubled(S, L, order, class_)
        class_ = UpdateClasses(order, class_, L)
        L = 2 * L
    return order


if __name__ == '__main__':
    text = input()
    suffix_array = BuildSuffixArray(text)
    for elem in suffix_array:
        print(elem, end=' ')