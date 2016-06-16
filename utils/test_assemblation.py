import subprocess
import os

import grade_result

if __name__ == "__main__":
    proc = subprocess.Popen(["./isbh ../feeds/feed3"], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()

    result = str(out)
    expected = ''

    with open('../feeds/feed3', 'r') as f:
        expected = f.readline()

    print(str(grade_result.similar(expected, str(out)[2:-1] )))

