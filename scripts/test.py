import argparse
import subprocess
import filecmp

import matplotlib.pyplot as plt

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--high', type=int, required=True, dest='high', help='high power of 2')
    parser.add_argument('--low', type=int, default=3, dest='low', help='low power of 2')
    args = parser.parse_args()

    exe_names = ['chain', 'cuckoo', 'double_hash', 'stl_wrapper']

    for exe_name in exe_names:
        res = dict(add=dict(), delete=dict(), search=dict())
        for i in range(args.low, args.high + 1):
            print(exe_name, "running for", i)
            opc = 2 ** i
            timelog = subprocess.run(
                ["../build/bin/" + exe_name, "./{0:03d}.dat".format(i), "./{0:03d}.res".format(i)],
                stderr=subprocess.PIPE
            ).stderr.decode('utf-8').split('\n')[opc : -1]

            if not filecmp.cmp("./{0:03d}.res".format(i), "./{0:03d}.ans".format(i)):
                exit(-1)

            for cmd in timelog:
                op, _, t = cmd.split()
                if opc not in res[op]:
                    res[op][opc] = list()
                res[op][opc].append(int(t))

        print("filtering data for", exe_name)
        for op, data in res.items():
            x, y = [], []
            for k, v in data.items():
                x.append(int(k))
                y.append(int(sum([int(j) for j in v]) / len(v)))
            fig, ax = plt.subplots()
            ax.set_xscale('log', basex=2)
            ax.set_xlabel('N')
            ax.set_ylabel('Clocks')
            ax.set_title(op)
            plt.plot(x, y, '^')
            plt.savefig(exe_name+ '_' + op + '.png')

if __name__ == "__main__":
    main()
