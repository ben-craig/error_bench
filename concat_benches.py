#!/usr/bin/env python3
import sys
import subprocess

def main():
    with open(sys.argv[1], 'wb') as fout:
        for name in sys.argv[2:]:
            res = subprocess.check_output([name])
            fout.write((name + "\t").encode('utf-8'))
            fout.write(res)

if __name__ == '__main__':
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
