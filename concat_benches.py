#!/usr/bin/env python3
import sys
import subprocess

def main():
    with open(sys.argv[1], 'wb') as fout:
      with open(sys.argv[2], 'r') as fin:
        for name in fin.read().split():
            res = subprocess.check_output([name])
            fout.write((name + ",").encode('utf-8'))
            fout.write(res)
            print(name)

if __name__ == '__main__':
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
