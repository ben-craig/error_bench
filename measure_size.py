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
    scanner = Scanner(r"^ \d\d\d\d:[0-9a-f]+ ([0-9a-f]+)H\s+([^\s]+)")
    result = 0
    returnOnFailure = False
    with open(map_file_name, 'r') as fin:
        for line in fin:
            if scanner.search(line):
                returnOnFailure = True
                section_name = scanner.matches.group(2)
                size_num = int(scanner.matches.group(1), 16)
                if ".text$" in section_name:
                    continue
                sym_size_map[section_name] = size_num
                result = result + size_num
            elif returnOnFailure:
                return result
    return result

BEFORE_BEGINNING = 0
BEGIN_FUNC = 1
IN_FUNC = 2

def measure_asm_size(asm_file_name, sym_size_map):
    asm_loc = Scanner(r"^  ([0-9A-F]+):(.*)")
    func = Scanner(r"^([^\s].*):$")
    state = BEFORE_BEGINNING
    addr = 0
    begin_addr_num = 0
    cur_func = "???"
    last_func = "???"
    addr_after_exit = 0
    needs_addr_after_exit = False
    result = 0
    with open(asm_file_name, 'r') as fin:
        for line in fin:
            if asm_loc.search(line):
                addr = int(asm_loc.matches.group(1), 16)
                if needs_addr_after_exit:
                    addr_after_exit = addr
                    needs_addr_after_exit = False
                if state == BEGIN_FUNC:
                    if addr_after_exit == 0:
                        addr_after_exit = addr
                    BLACK_LIST = ["_guard_dispatch_icall_nop", "strpbrk"]
                    if last_func not in BLACK_LIST:
                        size = (addr_after_exit - begin_addr_num)
                        sym_size_map[last_func] = size
                        result = result + size
                        needs_addr_after_exit = False
                    begin_addr_num = addr
                    addr_after_exit = 0
                if begin_addr_num == 0:
                    begin_addr_num = addr
                state = IN_FUNC
                instructions = asm_loc.matches.group(2)
                if instructions.endswith("call        dword ptr [__imp__ExitProcess@4]"):
                    needs_addr_after_exit = True
                if (" ret " in instructions) or (" jmp " in instructions) or instructions.endswith("__exit")  or instructions.endswith(" ret"):
                    needs_addr_after_exit = True
            if func.search(line):
                if state != BEFORE_BEGINNING:
                    state = BEGIN_FUNC
                last_func = cur_func
                cur_func = func.matches.group(1)
            if line == "  Summary":
                if state == IN_FUNC:
                    if addr_after_exit != 0:
                        size = (addr_after_exit - begin_addr_num)
                    else:
                        print ("Bias!", asm_file_name)
                        size = (addr - begin_addr_num)
                    sym_size_map[cur_func] = size
                    result = result + size
                return result
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
        'mapFile', help='name of a mapfile to analyze')
    parser.add_argument(
        'outputFile', help='output file to create that will hold size')
    parser.add_argument(
        '-d',
        '--diff',
        help="Name of second mapfile to diff against",
        action="store",
        dest="diffFile",
        default="")
    args = parser.parse_args()
    first_sym_size_map = {}
    map_size = measure_map_size(args.mapFile, first_sym_size_map)
    asm_name = args.mapFile.replace(".exe.map", ".exe.asm")
    asm_size = measure_asm_size(asm_name, first_sym_size_map)
    combined = map_size + asm_size
    if args.diffFile == "":
        with open(args.outputFile, 'w') as fout:
            fout.write(str(combined))
        return
    second_sym_size_map = {}
    measure_map_size(args.diffFile, second_sym_size_map)
    asm_name = args.diffFile.replace(".exe.map", ".exe.asm")
    measure_asm_size(asm_name, second_sym_size_map)
    diff(first_sym_size_map, second_sym_size_map, args.mapFile, args.diffFile, args.outputFile)

if __name__ == '__main__':
    import sys
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
