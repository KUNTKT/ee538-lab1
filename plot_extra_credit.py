#!/usr/bin/env python3
"""Plot extra-credit Strassen cutoff times from extra_credit_times.txt."""

import os
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))
SRC = os.path.join(ROOT, "extra_credit_times.txt")
OUT = os.path.join(ROOT, "extra_credit_h_vs_time.png")


def main():
    if not os.path.isfile(SRC):
        print("missing extra_credit_times.txt; run ./lab1 --extra first")
        return 1

    naive = None
    hs = []
    times = []
    with open(SRC) as f:
        for line in f:
            parts = line.strip().split()
            if not parts:
                continue
            if parts[0] == "naive":
                naive = int(parts[1])
            elif parts[0].isdigit():
                hs.append(int(parts[0]))
                times.append(int(parts[2]))

    try:
        import matplotlib

        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
    except Exception as exc:
        print("matplotlib unavailable:", exc)
        print("h times:", list(zip(hs, times)), "naive:", naive)
        return 0

    plt.figure(figsize=(7, 4.5))
    plt.plot(hs, times, marker="o", label="Strassen with cutoff 2^h")
    if naive is not None:
        plt.axhline(naive, linestyle="--", label="naive (%d)" % naive)
    plt.xlabel("h (stop recursion at 2^h)")
    plt.ylabel("clock() ticks")
    plt.title("Extra credit: runtime vs h (n=128, h=3..7)")
    plt.legend()
    plt.tight_layout()
    plt.savefig(OUT, dpi=120)
    print("wrote", OUT)
    return 0


if __name__ == "__main__":
    sys.exit(main())
