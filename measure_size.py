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

def measure_map_size(map_file_name):
    scanner = Scanner(r"^ \d\d\d\d:[0-9a-f]+ ([0-9a-f]+)H")
    result = 0
    returnOnFailure = False
    with open(map_file_name, 'r') as fin:
        for line in fin:
            if scanner.search(line):
                returnOnFailure = True
                result = result + int(scanner.matches.group(1), 16)
            elif returnOnFailure:
                return result
    return result

def main():
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument(
        'mapFile', help='name of a mapfile to analyze')
    parser.add_argument(
        'outputFile', help='output file to create that will hold size')
    args = parser.parse_args()
    result = measure_map_size(args.mapFile)
    with open(args.outputFile, 'w') as fout:
        fout.write(args.mapFile + "," + str(result) + "\n")

if __name__ == '__main__':
    import sys
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
