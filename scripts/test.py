#!/usr/bin/env python3

# import sys
import os

if __name__ == "__main__":
    for p in range(3,11):
        os.system("../build/bin/DSA <{0:02d}.dat >{1:02d}.txt".format(p, p))
        os.system("diff {0:02d}.ans {1:02d}.txt".format(p, p))
    
    # for p in range(3, 11):
    #     with open("{:02d}.txt".format(p), 'r', encoding='utf-8') as file1, open("{:02d}.ans".format(p), 'r', encoding='utf-8') as file2:
    #         lines1, lines2 = file1.readlines(), file2.readlines()

    #         if len(lines1) != len(lines2):
    #             print("file", p, "len error")
    #             sys.exit(-1)

    #         for idx in range(len(lines1)):
    #             if lines1[idx] != lines2[idx]:
    #                 print("file", p, "lines", idx)
    #                 sys.exit(-1)
    