#!/usr/bin/env python3
import sys

HEADER_STR = \
    "inc_global,inc_size,two_func,two_size,first_overhead,incr_cost,second_overhead\n"

def main():
    result_map = {}
    for name in sys.argv[2:]:
        with open(name, 'r') as fin:
            result_map[name] = fin.read()
    with open(sys.argv[1], 'w') as fout:
        fout.write(HEADER_STR)
        for key, value in result_map.items():
            if "two_func" in key:
                continue
            two_key = key.replace("inc_global", "two_func")
            parts = key.split("\\")
            parts[3] = "wont_throw"
            wont_throw_first_key = "\\".join(parts)
            wont_throw_second_key = wont_throw_first_key.replace("inc_global", "two_func")
            base_first = int(result_map[wont_throw_first_key])
            base_second = int(result_map[wont_throw_second_key])
            second_value = int(result_map[two_key])
            first_value = int(value)

            first_overhead = first_value - base_first
            second_cost = second_value - first_value
            wont_throw_diff = base_second - base_first
            second_overhead = second_cost - wont_throw_diff

            out_str = key + "," + value + "," + two_key + "," + str(second_value) + ","
            # calculated columns.
            out_str = out_str + str(first_overhead) + ","
            out_str = out_str + str(second_cost) + ","
            out_str = out_str + str(second_overhead) + "\n"
            fout.write(out_str)

if __name__ == '__main__':
    if sys.version_info[0] < 3:
        raise Error("Must be using Python 3")
    exit(main())
