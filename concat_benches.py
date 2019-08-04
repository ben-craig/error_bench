#!/usr/bin/env python3
import sys
import subprocess

CASES = ["happy,1","happy,16","sad,1","sad,16"]

def main():
  with open(sys.argv[1], 'wb') as fout:
    with open(sys.argv[2], 'r') as fin:
      for name in fin.read().split():
        res = subprocess.check_output([name])
        idx = 0
        for res_line in res.split():
          fout.write((name + "," + CASES[idx] + ",").encode('utf-8'))
          fout.write(res_line + "\n".encode('utf-8'))
          idx = idx + 1
        print(name)

if __name__ == '__main__':
  if sys.version_info[0] < 3:
    raise Error("Must be using Python 3")
  exit(main())
