#!/usr/bin/env python3

import re
import os

class Scanner(object):
    def __init__(self, expr):
        self.expr = expr
        self.cmpexpr = re.compile(expr)

    def search(self, string):
        self.matches = self.cmpexpr.search(string)
        return self.matches is not None

def asm_alignment(asm_file_name):
    scanner = Scanner(r"^  ([0-9a-f]+):.*call.*\bcaller\b")
    count = 0
    with open(asm_file_name, 'r') as fin:
        for line in fin:
            if scanner.search(line):
                if count == 0:
                    count = 1
                    continue
                addr = int(scanner.matches.group(1), 16)
                padding_needed = (64 - (addr % 64)) % 64
                return padding_needed
    print("Could not find second caller!\n")
    exit(2)

def main():
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument(
        'asmFile', help='name of asm file to analyze')
    args = parser.parse_args()
    result = asm_alignment(args.asmFile)
    if result == 0:
        return 0
    print("Needs an additional ", result, " padding bytes")
    return 1

if __name__ == '__main__':
    import sys
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
