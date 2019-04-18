#!/usr/bin/env python3

import re
import os

SERIES_PAIRS = [
  ["throw_exception", False],
  ["throw_struct", False],
  ["throw_val", False],
  ["stripped.outcome_std_error", "outcome_std_error"],
  ["stripped.outcome_struct", "outcome_struct"],
  ["stripped.outcome_val", "outcome_val"],
  ["stripped.tls_error_struct", "tls_error_struct"],
  ["stripped.tls_error_val", "tls_error_val"],
  ["stripped.expected_struct", "expected_struct"],
  ["stripped.expected_val", "expected_val"],
  ["stripped.ref_struct", "ref_struct"],
  ["stripped.return_struct", "return_struct"],
  ["stripped.ref_val", "ref_val"],
  ["stripped.return_val", "return_val"],
  ["noexcept_abort", False],
  ["stripped.abort", "abort"],
]

COLOR_PAIRS = [
  ["1b9e77", "5EC2A4"],
  ["d95f02", "FF9F55"],
  ["7570b3", "CFCDEA"],
  ["e7298a", "F27DB9"],
  ["66a61e", "A6DE66"],
  ["e6ab02", "FFD45B"],
  ["a6761d", "E6B965"],
  ["666666", "C4C3C3"],
]

def pair_idx_to_color_pair(pair_idx):
    color_idx = pair_idx % len(COLOR_PAIRS)
    return COLOR_PAIRS[color_idx]

def build_property_mapping():
    ord = 0
    pair_idx = 0
    mapping = {}
    for pair in SERIES_PAIRS:
        color_pair = pair_idx_to_color_pair(pair_idx)
        mapping[pair[0]] = [ord, color_pair[0]]
        ord = ord + 1
        if pair[1]:
            mapping[pair[1]] = [ord, color_pair[1]]
            ord = ord + 1
        pair_idx = pair_idx + 1
    return mapping

PROPERTY_MAPPING = build_property_mapping()

class SeriesData(object):
    def __init__(self, elt_map):
        self.plat = elt_map["plat"]
        self.type = elt_map["type"]
        self.ord = PROPERTY_MAPPING[self.type][0]
        self.color = PROPERTY_MAPPING[self.type][1]
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
        self.ord = seriesData.ord
        self.color = seriesData.color
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
