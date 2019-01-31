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

original_size = 0

def measure_map_size(map_file_name):
    scanner = Scanner(r"^ \d\d\d\d:[0-9a-f]+ ([0-9a-f]+)H\s+([^\s]+)")
    result = 0
    returnOnFailure = False
    with open(map_file_name, 'r') as fin:
        for line in fin:
            if scanner.search(line):
                returnOnFailure = True
                size_num = int(scanner.matches.group(1), 16)
                if ".text$" in scanner.matches.group(2):
                    global original_size
                    original_size = original_size + size_num
                    continue
                result = result + size_num
            elif returnOnFailure:
                return result
    return result

BEFORE_BEGINNING = 0
BEGIN_FUNC = 1
IN_FUNC = 2
PAST_FUNC = 3

def measure_asm_size(asm_file_name):
    asm_loc = Scanner(r"^  ([0-9A-F]+):(.*)")
    func = Scanner(r"^([^\s]+):$")
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
                if state == BEGIN_FUNC and addr_after_exit != 0:
                    if last_func != "strpbrk":
                        size = (addr_after_exit - begin_addr_num)
                        #print(last_func, size)
                        result = result + size
                    begin_addr_num = addr
                    addr_after_exit = 0
                if begin_addr_num == 0:
                    begin_addr_num = addr
                state = IN_FUNC
                instructions = asm_loc.matches.group(2)
                if instructions.endswith(" ret") or (" jmp " in instructions):
                    needs_addr_after_exit = True
            if func.search(line):
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
                    #print(cur_func, size)
                    result = result + size
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
    map_size = measure_map_size(args.mapFile)
    asm_name = args.mapFile.replace(".exe.map", ".exe.asm")
    asm_size = measure_asm_size(asm_name)
    combined = map_size + asm_size
    global original_size
    #print(asm_name, original_size, asm_size, original_size - asm_size)
    with open(args.outputFile, 'w') as fout:
        fout.write(str(combined))

if __name__ == '__main__':
    import sys
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
