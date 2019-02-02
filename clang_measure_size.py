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
    scanner = Scanner(r"^\s*\d+\s+[^\s]+\s+([a-f0-9]+)\s+")
    typeScanner = Scanner(r"^[A-Z\s,]+$")
    result = 0
    cur_size = 0
    with open(map_file_name, 'r') as fin:
        for line in fin:
            if line.startswith("Disassembly"):
                return result
            if scanner.search(line):
                cur_size = int(scanner.matches.group(1), 16)
                continue
            if cur_size and typeScanner.search(line):
                if " CODE" in line:
                    continue
                result = result + cur_size
                cur_size = 0
    return result

def measure_asm_size(asm_file_name):
    asm_loc = Scanner(r"^  ([0-9a-f]+):\s+((?:[0-9a-f]{2} ))+")
    func = Scanner(r"^([0-9a-f]+)\s+\<([^>]*)\>:$")
    addr_end = 0
    begin_addr_num = 0
    cur_func = "???"
    result = 0
    with open(asm_file_name, 'r') as fin:
        for line in fin:
            if asm_loc.search(line):
                addr = int(asm_loc.matches.group(1), 16)
                instrs = asm_loc.matches.group(2)
                addr_end = len(instrs)/3 + addr
            if func.search(line):
                last_size = (addr_end - begin_addr_num)
                #print(cur_func, last_size)
                result = result + last_size
                begin_addr_num = int(func.matches.group(1), 16)
                addr_end = begin_addr_num
                cur_func = func.matches.group(2)

    # report the very last function as well
    last_size = (addr_end - begin_addr_num)
    #print(cur_func, last_size)
    result = result + last_size
    return result

def main():
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument(
        'asmFile', help='name of a assembly file to analyze')
    parser.add_argument(
        'outputFile', help='output file to create that will hold size')
    args = parser.parse_args()
    map_size = measure_map_size(args.asmFile)
    asm_size = measure_asm_size(args.asmFile)
    combined = map_size + asm_size
    with open(args.outputFile, 'w') as fout:
        fout.write(str(combined))

if __name__ == '__main__':
    import sys
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
