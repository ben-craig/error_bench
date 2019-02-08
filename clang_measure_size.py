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

def measure_map_size(map_file_name, sym_size_map):
    scanner = Scanner(r"^\s*\d+\s+([^\s]+)\s+([a-f0-9]+)\s+")
    typeScanner = Scanner(r"^[A-Z\s,]+$")
    result = 0
    cur_size = 0
    with open(map_file_name, 'r') as fin:
        for line in fin:
            if line.startswith("Disassembly"):
                return result
            if scanner.search(line):
                cur_size = int(scanner.matches.group(2), 16)
                cur_name = scanner.matches.group(1)
                continue
            if cur_size and typeScanner.search(line):
                if " CODE" in line:
                    continue
                sym_size_map[cur_name] = cur_size
                result = result + cur_size
                cur_size = 0
    return result

def measure_asm_size(asm_file_name, sym_size_map):
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
                addr_end = int(len(instrs)/3 + addr)
            if func.search(line):
                last_size = (addr_end - begin_addr_num)
                sym_size_map[cur_func] = last_size
                result = result + last_size
                begin_addr_num = int(func.matches.group(1), 16)
                addr_end = begin_addr_num
                cur_func = func.matches.group(2)

    # report the very last function as well
    last_size = (addr_end - begin_addr_num)
    sym_size_map[cur_func] = last_size
    result = result + last_size
    return result

def diff(map_one, map_two, fname1, fname2, out_file_name):
    diff_map = {}
    only_one = {}
    only_two = {}
    for key, value in map_one.items():
        if key in map_two:
            distance = map_two[key] - value
            if distance != 0:
                diff_map[key] = distance
        else:
            only_one[key] = value
    for key, value in map_two.items():
        if key not in map_one:
            only_two[key] = value
    with open(out_file_name, 'w') as fout:
        fout.write(fname2 + " - " + fname1 + "\n")
        for key, value in sorted(diff_map.items()):
            fout.write(key + ": " + str(value) + "  before(" + str(map_one[key]) + ") after(" + str(map_two[key]) + ")\n")
        fout.write("\nadded in " + fname2 + "\n")
        for key, value in sorted(only_two.items()):
            fout.write(key + ": " + str(value) + "\n")
        fout.write("\nremoved in " + fname2 + "\n")
        for key, value in sorted(only_one.items()):
            fout.write(key + ": " + str(value) + "\n")

def main():
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument(
        'asmFile', help='name of a assembly file to analyze')
    parser.add_argument(
        'outputFile', help='output file to create that will hold size')
    parser.add_argument(
        '-d',
        '--diff',
        help="Name of second assembly file to diff against"
        action="store",
        dest="diffFile",
        default="")
    args = parser.parse_args()
    first_sym_size_map = {}
    map_size = measure_map_size(args.asmFile, first_sym_size_map)
    asm_size = measure_asm_size(args.asmFile, first_sym_size_map)
    combined = map_size + asm_size
    if args.diffFile == "":
        with open(args.outputFile, 'w') as fout:
            fout.write(str(combined))
        return
    second_sym_size_map = {}
    measure_map_size(args.diffFile, second_sym_size_map)
    measure_asm_size(args.diffFile, second_sym_size_map)
    diff(first_sym_size_map, second_sym_size_map, args.mapFile, args.diffFile, args.outputFile)

if __name__ == '__main__':
    import sys
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
