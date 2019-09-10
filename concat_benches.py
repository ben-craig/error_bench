#!/usr/bin/env python3
import sys
import subprocess

CASES = ["happy,8","sad,8","happy_param,8","sad_param,8","happy_ret,8","sad_ret,8","happy_ret_nd,8","sad_ret_nd,8"]

def main():
  with open(sys.argv[1], 'w') as fout:
    with open(sys.argv[2], 'r') as fin:
      for name in fin.read().split():
        res = subprocess.check_output([name])
        idx = 0
        lines = res.decode('utf-8').split()
        out_name = name.replace('/','\\')
        for res_line in lines:
          fout.write(out_name + "," + CASES[idx] + "," + res_line + "\n")
          idx = idx + 1
        print(out_name)

if __name__ == '__main__':
  exit(main())
