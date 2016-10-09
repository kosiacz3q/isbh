import sys


def longest_common_substring(s1, s2):
    m = [[0] * (1 + len(s2)) for i in range(1 + len(s1))]
    longest, x_longest = 0, 0
    for x in range(1, 1 + len(s1)):
        for y in range(1, 1 + len(s2)):
            if s1[x - 1] == s2[y - 1]:
                m[x][y] = m[x - 1][y - 1] + 1
                if m[x][y] > longest:
                    longest = m[x][y]
                    x_longest = x
            else:
                m[x][y] = 0
    return s1[x_longest - longest: x_longest]


def levenshtein(s1, s2):
    if len(s1) < len(s2):
        return levenshtein(s2, s1)

    # len(s1) >= len(s2)
    if len(s2) == 0:
        return len(s1)

    previous_row = range(len(s2) + 1)
    for i, c1 in enumerate(s1):
        current_row = [i + 1]
        for j, c2 in enumerate(s2):
            insertions = previous_row[
                             j + 1] + 1  # j+1 instead of j since previous_row and current_row are one character longer
            deletions = current_row[j] + 1  # than s2
            substitutions = previous_row[j] + (c1 != c2)
            current_row.append(min(insertions, deletions, substitutions))
        previous_row = current_row

    return previous_row[-1]


def av(list):
    wynik = result()
    temp = 0
    for element in list:
        wynik.lcs += element.lcs
        wynik.leve += element.leve
        wynik.normalised_dist += element.normalised_dist
        wynik.normalised_lcs += element.normalised_lcs
        wynik.base += element.base
        wynik.length += element.length
        temp += 1

    wynik.length /= temp    
    wynik.lcs /= temp
    wynik.leve /= temp
    wynik.normalised_dist /= temp
    wynik.normalised_lcs /= temp
    wynik.base /= temp
    return wynik


class result:
    lcs = 0
    leve = 0
    normalised_dist = 0
    normalised_lcs = 0
    base = 0
    length = 0

    def run(self, first, second):
        self.base = len(first)
        self.lcs = len(longest_common_substring(first, second))
        self.leve = levenshtein(first, second)
        self.normalised_dist = 1.0 - self.leve / len(second)
        self.normalised_lcs = self.lcs/self.base
        self.length = len(second)


    def show(self):
        print("len: " + self.length.__str__())
        print("LCS: " + self.lcs.__str__())
        print("normalised LCS: " + self.normalised_lcs.__str__())
        print("levenshtein distace: " + self.leve.__str__())
        print("normalised distance: " + self.normalised_dist.__str__())


def make_test():
    if len(sys.argv) > 1:
        f = open(sys.argv[1])
        base = f.readline()[:-1]
        temp = []

        for line in f:
            wyn = result()
            wyn.run(base, line[:-1])
            temp.append(wyn)
            #wyn.show()

        res = av(temp)


        res.show()


make_test()







