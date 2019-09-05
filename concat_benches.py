#!/usr/bin/env python3
import sys
import subprocess

CASES = ["happy,16","happy,15","sad,16","sad,15"]

def main():
  with open(sys.argv[1], 'w') as fout:
    with open(sys.argv[2], 'r') as fin:
      for name in fin.read().split():
        res = subprocess.check_output([name])
        idx = 0
        lines = res.decode('utf-8').split()
        (happy_16, happy_15, sad_16, sad_15) = lines
        for res_line in lines:
          fout.write(name + "," + CASES[idx] + "," + res_line + "\n")
          idx = idx + 1
        fout.write(name + ",happy,1,{:.4f}\n".format(float(happy_16)-float(happy_15)))
        fout.write(name + ",sad,1,{:.4f}\n".format(float(sad_16)-float(sad_15)))
        print(name)

if __name__ == '__main__':
  if sys.version_info[0] < 3:
    raise Error("Must be using Python 3")
  exit(main())
