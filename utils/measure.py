from os import listdir
from os.path import isfile, join
import sys
import subprocess
from difflib import SequenceMatcher
from threading import Thread, Event
import time


def measure_file(currentFeed):
    exec_cmd = "./isbh " + currentFeed

    proc = subprocess.Popen([exec_cmd], stdout=subprocess.PIPE, shell=True)

    timeout_seconds = 1800

    try:
        (out, err) = proc.communicate(timeout=timeout_seconds)

        result = str(out)[2:-3]
        expected = ''

        with open(currentFeed, 'r') as f:
            expected = f.readline().strip()

        seq = result.split(';')[-1].strip()
        # print(seq)
        # print(expected)


        match_ratio = SequenceMatcher(None, expected, seq).ratio()

        print(currentFeed + ";" + str(match_ratio) + ";" + result)
    except subprocess.TimeoutExpired:
        print(currentFeed + ";" + str(0) + ";>" + str(timeout_seconds) + ";-")


def measure(dir):
    print("file; match; time spent; result;")
    for file in [f for f in listdir(dir) if isfile(join(dir, f))]:
        currentFeed = join(dir, file)
        measure_file(currentFeed)

if __name__ == "__main__":
    measure(sys.argv[1])