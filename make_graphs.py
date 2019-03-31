#!/usr/bin/env python3

import re
import os

ORDINAL_MAPPING = {
  "expected_struct" :            16,
  "expected_val" :               15,
  "noexcept_abort" :         10,
  "ref_struct" :                 14,
  "ref_val" :                    13,
  "return_struct" :              12,
  "return_val" :                 11,
  "stripped.expected_struct" :   6,
  "stripped.expected_val" :      5,
  "stripped.ref_struct" :        4,
  "stripped.ref_val" :           3,
  "stripped.return_struct" :     2,
  "stripped.return_val" :        1,
  "stripped.abort" :         0,
  "stripped.tls_error_struct" :  8,
  "stripped.tls_error_val" :     7,
  "abort" :                  9,
  "throw_exception" :            21,
  "throw_struct" :               20,
  "throw_val" :                  19,
  "tls_error_struct" :           18,
  "tls_error_val" :              17,
}


class SeriesData(object):
    def __init__(self, elt_map):
        self.plat = elt_map["plat"]
        self.type = elt_map["type"]
        self.ord = ORDINAL_MAPPING[self.type]
        self.eltMap = elt_map
        self.cmpTerm = elt_map["CmpTerm"]
        self.cost2ndNeutral = elt_map["Cost2ndNeutral"]
        self.cost1stError = elt_map["Cost1stError"]
        self.cost2ndError = elt_map["Cost2ndError"]
        self.cost1stCatch = elt_map["Cost1stCatch"]
        if "Cost2ndCatch" not in elt_map:
            print(elt_map)
            raise elt_map
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
                headers = line.split(',')
                continue
            tmp = line.split(',')
            elt = {}
            for i in range(len(tmp)):
                elt[headers[i]] = tmp[i]
            seriesData = SeriesData(elt)
            if seriesData.ord not in data:
                data[seriesData.ord] = SeriesTypeData(seriesData)
            else:
                data[seriesData.ord].plat_map[seriesData.plat] = seriesData

    with open(out_name, 'w') as fout:
        spaces = "  "

        cases = [
            "CmpTerm",
            "Cost2ndNeutral",
            "Cost1stError",
            "Cost2ndError",
            "Cost1stCatch",
            "Cost2ndCatch",
        ]
        
        for case in cases:
            fout.write("var data_" + case + " = [\n")
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
            fout.write("];\n\n");

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
