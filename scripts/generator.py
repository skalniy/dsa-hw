#!/usr/bin/env python3

from enum import Enum
import random
import sys

OP = Enum('OP', 'ADD DELETE SEARCH')

if __name__ == "__main__":
    for p in range(3,11):
        with open("./{:02d}.dat".format(p), 'w', encoding='utf-8') as i_file, open("./{:02d}.ans".format(p), 'w', encoding='utf-8') as o_file:
            op_count = 2**p
            ht = dict()
            for _ in range(op_count):
                op = random.choice(list(OP))
                key = random.randrange(int(op_count/3))
                if op == OP.ADD:
                    data = random.randint(-2**30, 2**30)
                    i_file.write("{0:s} {1:d} {2:d}\n".format("add", key, data))
                    if not key in ht.keys():
                        ht[key] = data
                        o_file.write("OK\n")
                    else:
                        o_file.write("FAIL\n")
                elif op == OP.DELETE:
                    i_file.write("{0:s} {1:d}\n".format("delete", key))
                    o_file.write(("OK" if ht.pop(key, None) else "FAIL") + '\n')
                elif op == OP.SEARCH:
                    i_file.write("{0:s} {1:d}\n".format("search", key))
                    o_file.write(str(ht.get(key, "null")) + '\n')
                else:
                    sys.exit(-1)
