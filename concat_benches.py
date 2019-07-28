#!/usr/bin/env python3
import sys
import subprocess

SIZES = [1,2,4,8,16]

def main():
  with open(sys.argv[1], 'wb') as fout:
    with open(sys.argv[2], 'r') as fin:
      for name in fin.read().split():
        res = subprocess.check_output([name])
        idx = 0
        for res_line in res.split():
          fout.write((name + "," + str(SIZES[idx]) + ",").encode('utf-8'))
          fout.write(res_line + "\n".encode('utf-8'))
          idx = idx + 1
        print(name)

if __name__ == '__main__':
  if sys.version_info[0] < 3:
    raise Error("Must be using Python 3")
  exit(main())
