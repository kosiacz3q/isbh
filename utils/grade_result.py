from difflib import SequenceMatcher
import sys

def similar(a, b):
    print("expected :" + a)
    print("given    :" + b)
    return SequenceMatcher(None, a, b).ratio()

if __name__ == "__main__":
    print(similar(sys.argv[1], sys.argv[2]))