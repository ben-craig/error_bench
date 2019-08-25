#!/usr/bin/env python3
import sys
import subprocess

def main():
  with open(sys.argv[2], 'w') as fout:
    with open(sys.argv[1], 'r') as fin:
      current_int = int(sys.argv[3])
      if current_int == 15:
        next_func = "callee"
      else:
        next_val = str(current_int + 1)
        next_func = "caller" + next_val
      contents = fin.read().replace("__VALUE__", sys.argv[3]).replace("__NEXT_FUNC__", next_func)
      fout.write(contents)

if __name__ == '__main__':
  exit(main())
