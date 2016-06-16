import sys

def partial_sum(seq):
    sum = 0
    for c in seq:
        if c == 'a' or c == 't':
            sum += 2
        else:
            sum += 4

    # print("sequence [" + seq + "] val [" + str(sum) + "]")
    return sum

def cut_sequence(sequence, outputfile):

    with open(outputfile, 'w') as out:
        start = 0
        end = 0

        out.write(sequence + "\n")

        dic = {}

        first = True

        first_oligo = ""
        last_oligo = ""

        while end < len(sequence):

            end = start + 1

            while end + 1 < len(sequence) and partial_sum(sequence[start:end + 2]) <= 12:
                end += 1

            cur_seq = sequence[start:end + 1]

            if first:
                first = False
                first_oligo = cur_seq

            if (cur_seq in dic):
                dic[cur_seq] += 1
            else:
                dic[cur_seq] = 1

            start += 1

            if end + 1 == len(sequence):
                last_oligo = cur_seq
                break

        out.write(first_oligo + "\n")
        out.write(last_oligo + "\n")

        for k, v in dic.items():
            out.write(k + " " + str(v) + "\n")

if __name__ == "__main__":
    cut_sequence(sys.argv[1], sys.argv[2])