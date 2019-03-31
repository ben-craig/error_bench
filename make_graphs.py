#!/usr/bin/env python3

import re
import os

class SeriesData(object):
    def __init__(self, elt_map):
        self.plat = elt_map["plat"]
        self.ord = int(elt_map["Ord"])
        self.type = elt_map["type"]
        self.eltMap = elt_map
        self.cmpTerm = elt_map["CmpTerm"]
        self.cost2ndNeutral = elt_map["Cost2ndNeutral"]
        self.cost1stError = elt_map["Cost1stError"]
        self.cost2ndError = elt_map["Cost2ndError"]
        self.cost1stCatch = elt_map["Cost1stCatch"]
        self.cost2ndCatch = elt_map["Cost2ndCatch"]

class SeriesTypeData(object):
    def __init__(self, seriesData):
        self.type = seriesData.type
        self.ord = int(seriesData.ord)
        self.plat_map = {seriesData.plat: seriesData}

def make_graphs(tsv_name, out_name):
    data = {}
    with open(tsv_name, 'r') as fin:
        first = True
        for line in fin:
            if first:
                first = False
                headers = line.split('\t')
                continue
            tmp = line.split('\t')
            elt = {}
            for i in range(len(tmp)):
                elt[headers[i]] = tmp[i]
            seriesData = SeriesData(elt)
            if seriesData.ord not in data:
                data[seriesData.ord] = SeriesTypeData(seriesData)
            else:
                data[seriesData.ord].plat_map[seriesData.plat] = seriesData

    with open(out_name, 'w') as fout:
        spaces = "" #" "*8

        cases = [
            "CmpTerm",
            "Cost2ndNeutral",
            "Cost1stError",
            "Cost2ndError",
            "Cost1stCatch",
            "Cost2ndCatch",
        ]
        
        for case in cases:
            fout.write(case + "\n\n")
            first = True
            for ord in sorted(data.keys()):
                if not first:
                    fout.write(spaces + "},\n")
                else:
                    first = False
                fout.write(spaces + "{\n")
                fout.write(spaces + "  type: 'bar',\n")
                fout.write(spaces + "  name: '" + data[ord].type + "',\n")
                if ord == len(data) - 1:
                    fout.write(spaces + "  barCategoryGap: '10%',\n")
                fout.write(spaces + "  data: [" +
                    data[ord].plat_map["Clang/x64"].eltMap[case] + "," +
                    data[ord].plat_map["GCC/x64"].eltMap[case] + "," +
                    data[ord].plat_map["MSVC/x64"].eltMap[case] + "," +
                    data[ord].plat_map["MSVC/x86"].eltMap[case] + "]\n")
            fout.write(spaces + "}\n")

def main():
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument(
        'tsv', help='name of tab seperated value file to analyze')
    parser.add_argument(
        'outputFile', help='output file to create that will hold graph snippets')
    args = parser.parse_args()
    make_graphs(args.tsv, args.outputFile)

if __name__ == '__main__':
    import sys
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
