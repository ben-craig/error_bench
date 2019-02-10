#!/usr/bin/env python3
import sys
import os

HEADER_STR = ",".join([
    "plat",
    "type",
    "First Neutral",
    "CmpTerm",
    "Second Neutral",
    "Cost2ndNeutral",
    "First Error",
    "Cost1stError",
    "Second Error",
    "Cost2ndError",
    "First Catch",
    "Cost1stCatch",
    "Second Catch",
    "Cost2ndCatch"
])+"\n"

def diff(fout, plat, error_type, test_cases, terminate_test_cases):
    firstCatch = 0
    if "one_catch__" in test_cases:
        firstCatch = test_cases["one_catch__"]-test_cases["two_error__"]

    string = ",".join([
        plat,
        error_type,
        str(test_cases["one_neutral"]),
        str(test_cases["one_neutral"] - terminate_test_cases["one_neutral"]),
        str(test_cases["two_neutral"]),
        str(test_cases["two_neutral"]-test_cases["one_neutral"]),
        str(test_cases["one_error__"]),
        str(test_cases["one_error__"]-test_cases["two_neutral"]),
        str(test_cases["two_error__"]),
        str(test_cases["two_error__"]-test_cases["one_error__"]),
        str(test_cases.get("one_catch__", 0)),
        str(firstCatch),
        str(test_cases.get("two_catch__", 0)),
        str(test_cases.get("two_catch__", 0)-test_cases.get("one_catch__",0)),
    ])
    fout.write(string + "\n")

def name_to_plat(name):
    return "Windows/" + name.split(os.path.sep)[0]

def name_to_case(name):
    return name.split(os.path.sep)[1]

def name_to_error_type(name):
    if (os.path.sep + "noexcept.") in name:
        return "stripped." + name.split(os.path.sep)[2]
    return name.split(os.path.sep)[2]

def main():
    plat_map = {}
    for name in sys.argv[2:]:
        with open(name, 'r') as fin:
            value = int(fin.read())

            plat =  name_to_plat(name)
            error_type = name_to_error_type(name)
            test_case = name_to_case(name)
            if plat not in plat_map:
                plat_map[plat] = {}
            if error_type not in plat_map[plat]:
                plat_map[plat][error_type] = {}
            plat_map[plat][error_type][test_case] = int(value)

    with open(sys.argv[1], 'w') as fout:
        fout.write(HEADER_STR)
        for plat, error_types in plat_map.items():
            for error_type, test_cases in error_types.items():
                diff(fout, plat, error_type, test_cases, error_types["stripped.terminate_________"])

if __name__ == '__main__':
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
