#!/usr/bin/env python3
import sys

HEADER_STR = \
    "proc,flags,type,case_one,one_size,case_two,two_size,first_overhead,incr_cost,second_overhead\n"

def name_to_pivots(name):
    return ",".join(name.split("\\")[0:2])

def name_to_error_type(name):
    return name.split("\\")[3]

def name_to_case(name):
    return name.split("\\")[2]

def diff(fout, key, value, result_map, substr1, substr2):
    two_key = key.replace(substr1, substr2)
    if two_key not in result_map:
        return
    parts = key.split("\\")
    parts[3] = "terminate"
    wont_throw_first_key = "\\".join(parts)
    wont_throw_second_key = wont_throw_first_key.replace(substr1, substr2)
    base_first = int(result_map.get(wont_throw_first_key, 0))
    base_second = int(result_map.get(wont_throw_second_key, 0))
    second_value = int(result_map[two_key])
    first_value = int(value)

    first_overhead = first_value - base_first
    second_cost = second_value - first_value
    wont_throw_diff = base_second - base_first
    second_overhead = second_cost - wont_throw_diff

    out_str = name_to_pivots(key) + "," + name_to_error_type(key) + ","
    out_str = out_str + name_to_case(key) + "," + value + ","
    out_str = out_str + name_to_case(two_key) + "," + str(second_value) + ","
    # calculated columns.
    out_str = out_str + str(first_overhead) + ","
    out_str = out_str + str(second_cost) + ","
    out_str = out_str + str(second_overhead) + "\n"
    fout.write(out_str)

def main():
    result_map = {}
    for name in sys.argv[2:]:
        with open(name, 'r') as fin:
            result_map[name] = fin.read()
    with open(sys.argv[1], 'w') as fout:
        fout.write(HEADER_STR)
        for key, value in result_map.items():
            if "\\two_" in key:
                if "\\two_neutral\\" in key:
                    diff(fout, key, value, result_map, "\\two_neutral", "\\one_error")
                    diff(fout, key, value, result_map, "\\two_neutral", "\\one_catch")
                continue
            diff(fout, key, value, result_map, "\\one_", "\\two_")

if __name__ == '__main__':
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
