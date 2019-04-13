#!/usr/bin/env python3

import re
import os

ORDINAL_MAPPING = {
  "throw_exception" :            0,
  "throw_struct" :               1,
  "throw_val" :                  2,
  "noexcept_abort" :             3,
  "stripped.abort" :             4,
  "abort" :                      5,
  "stripped.tls_error_val" :     6,
  "tls_error_val" :              7,
  "stripped.tls_error_struct" :  8,
  "tls_error_struct" :           9,
  "stripped.ref_val" :           10,
  "ref_val" :                    11,
  "stripped.return_val" :        12,
  "return_val" :                 13,
  "stripped.ref_struct" :        14,
  "ref_struct" :                 15,
  "stripped.return_struct" :     16,
  "return_struct" :              17,
  "stripped.expected_val" :      18,
  "expected_val" :               19,
  "stripped.outcome_val" :       20,
  "outcome_val" :                21,
  "stripped.expected_struct" :   22,
  "expected_struct" :            23,
  "stripped.outcome_struct" :    24,
  "outcome_struct" :             25,
  "stripped.outcome_std_error" : 26,
  "outcome_std_error" :          27,
}

#1b9e77 5EC2A4
#d95f02 FF9F55
#7570b3 CFCDEA
#e7298a F27DB9
#66a61e A6DE66
#e6ab02 FFD45B
#a6761d E6B965
#666666 C4C3C3

COLOR_MAPPING = {
  "throw_exception" :            "1b9e77",
  "throw_struct" :               "d95f02",
  "throw_val" :                  "7570b3",
  "noexcept_abort" :             "e7298a",
  "stripped.abort" :             "66a61e",
  "abort" :                      "A6DE66",
  "stripped.ref_val" :           "e6ab02",
  "ref_val" :                    "FFD45B",
  "stripped.return_val" :        "a6761d",
  "return_val" :                 "E6B965",
  "stripped.ref_struct" :        "666666",
  "ref_struct" :                 "C4C3C3",
  "stripped.return_struct" :     "1b9e77",
  "return_struct" :              "5EC2A4",
  "stripped.outcome_val" :       "d95f02",
  "outcome_val" :                "FF9F55",
  "stripped.expected_val" :      "7570b3",
  "expected_val" :               "CFCDEA",
  "stripped.outcome_struct" :    "e7298a",
  "outcome_struct" :             "F27DB9",
  "stripped.expected_struct" :   "66a61e",
  "expected_struct" :            "A6DE66",
  "stripped.tls_error_val" :     "e6ab02",
  "tls_error_val" :              "FFD45B",
  "stripped.tls_error_struct" :  "a6761d",
  "tls_error_struct" :           "E6B965",
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
        self.stack_type = seriesData.type.replace("stripped.","")
        self.ord = int(seriesData.ord)
        self.color = COLOR_MAPPING[self.type]
        self.plat_map = {seriesData.plat: seriesData}

def is_all_zeroes(series_type_data, case):
    return \
        (series_type_data.plat_map["Clang/x64"].eltMap[case] == "0") and \
        (series_type_data.plat_map["GCC/x64"].eltMap[case] == "0"  ) and \
        (series_type_data.plat_map["MSVC/x64"].eltMap[case] == "0" ) and \
        (series_type_data.plat_map["MSVC/x86"].eltMap[case] == "0" )


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
                if is_all_zeroes(data[ord], case):
                    continue
                if not first:
                    fout.write(spaces + "},\n")
                else:
                    first = False
                fout.write(spaces + "{\n")
                fout.write(spaces + "  type: 'bar',\n")
                fout.write(spaces + "  name: '" + data[ord].type + "',\n")
                fout.write(spaces + "  stack: '" + data[ord].stack_type + "',\n")
                fout.write(spaces + "  itemStyle: {color: '#" + data[ord].color + "'},\n"),
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
