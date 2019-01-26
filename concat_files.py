#!/usr/bin/env python3
import sys

def main():
    with open(sys.argv[1], 'w') as fout:
        for name in sys.argv[2:]:
            with open(name, 'r') as fin:
                fout.write(fin.read())

if __name__ == '__main__':
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
