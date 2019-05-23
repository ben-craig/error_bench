#!/usr/bin/env python3
import sys
from shutil import copyfile

def main():
    copyfile(sys.argv[2], sys.argv[1])    

if __name__ == '__main__':
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
