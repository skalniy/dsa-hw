import argparse
from enum import Enum
import random

def generate(size_lg):
    with    open("./{0:03d}.dat".format(size_lg), 'w', encoding='utf-8') as i_file, \
            open("./{0:03d}.ans".format(size_lg), 'w', encoding='utf-8') as o_file:
        OP = Enum('OP', 'ADD DELETE SEARCH MIN MAX')
        size = 2 ** size_lg
        ht = dict()

        keys = random.sample(range(-size, size), size)
        i_file.write("{0:d}\n".format(size * 4))
        for key in keys:
            if not key in ht.keys():
                i_file.write("{0:s} {1:d} {1:d}\n".format("add", key))
                ht[key] = key
                o_file.write("true\n")

        for _ in range(10000):
            op = random.choice(list(OP))
            key = random.randrange(-size, size)

            if op == OP.ADD:
                i_file.write("{0:s} {1:d} {1:d}\n".format("add", key, key))
                if not key in ht.keys():
                    ht[key] = key
                    o_file.write("true\n")
                else:
                    o_file.write("false\n")
            elif op == OP.DELETE:
                i_file.write("{0:s} {1:d}\n".format("delete", key))
                o_file.write(("true" if ht.pop(key, None) is not None else "false") + '\n')
            elif op == OP.SEARCH:
                i_file.write("{0:s} {1:d}\n".format("search", key))
                o_file.write(str(ht.get(key, "null")) + '\n')
            elif op == OP.MIN:
                i_file.write("min\n")
                o_file.write("{0:d} {0:d}\n".format(min(ht.keys())) 
                    if len(ht) else "null\n")
            elif op == OP.MAX:
                i_file.write("max\n")
                o_file.write("{0:d} {0:d}\n".format(max(ht.keys())) 
                    if len(ht) else "null\n")
            else:
                exit(-1)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--high', type=int, required=True, dest='high',
        help='high power of 2')
    parser.add_argument('--low', type=int, default=3, dest='low',
        help='low power of 2')
    args = parser.parse_args()

    for i in range(args.low, args.high + 1):
        print("generating for {0:d}".format(i))
        generate(i)
