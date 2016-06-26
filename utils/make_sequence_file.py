import sys
import random

def partial_sum(seq):
    sum = 0
    for c in seq:
        if c == 'a' or c == 't':
            sum += 2
        else:
            sum += 4

    return sum


def cut_sequence(sequence, temperature, error_percentage, outputfile):

    with open(outputfile, 'w') as out:
        start = 0
        end = 0

        out.write(sequence + "\n")

        dic = {}

        first = True
        first_oligo = ""

        last_end = start

        while end < len(sequence):

            end = start + 1

            while end + 1 < len(sequence) and partial_sum(sequence[start:end + 2]) <= temperature:
                end += 1

            if last_end < end and partial_sum(sequence[start:end + 1]) in [temperature, temperature - 2]:

                cur_seq = sequence[start:end + 1]

                if first:
                    first = False
                    first_oligo = cur_seq

                if (cur_seq in dic):
                    dic[cur_seq] += 1
                else:
                    dic[cur_seq] = 1

                last_end = end

            start += 1

        out.write(first_oligo + "\n")


        for k, v in dic.items():
            if k != first_oligo:
                if random.randrange(0,100,1) < error_percentage:
                    continue

            # out.write('graphCreator.add(Oligo("' + k + "\"," + str(v) + "));\n")
            out.write(k + " " + str(v) + "\n")


if __name__ == "__main__":

    if len(sys.argv) == 5:
        cut_sequence(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]), sys.argv[4])
    elif len(sys.argv) == 6 and sys.argv[1] == 'random':
        sequence = ""
        i =  int(sys.argv[2])

        while (i > 0):
            sequence += random.choice(['a', 'c', 't', 'g'])
            i -= 1

        cut_sequence(sequence, int(sys.argv[3]), int(sys.argv[4]) , sys.argv[5])

    else:
        print("Invalid arguments")
        print("Use:")
        print("[1] make_sequence_file <sequence> <temperature> <error percentage> <output_file>")
        print("[2] make_sequence_file random <length> <temperature> <error percentage> <output_file>")




