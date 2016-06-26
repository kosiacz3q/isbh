from os import listdir
from os.path import isfile, join
import sys
import subprocess



def measure(dir):
    for file in [f for f in listdir(dir) if isfile(join(dir, f))]:
        currentFeed = join(dir, file)
        print("current file is " + currentFeed)
        exec_cmd = "./isbh " + currentFeed


        proc = subprocess.Popen([exec_cmd], stdout=subprocess.PIPE, shell=True)
        (out, err) = proc.communicate()

        result = str(out)

        print(result)

if __name__ == "__main__":
    measure(sys.argv[1])