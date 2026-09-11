#!/usr/bin/env python3
"""Local-only correctness checks. Does not replace Q1/Q2 and is not submitted."""

import os
import shutil
import subprocess
import sys
import tempfile


ROOT = os.path.dirname(os.path.abspath(__file__))
BINARY = os.path.join(ROOT, "lab1")


def naive(A, B):
    n = len(A)
    C = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            s = 0
            for k in range(n):
                s += A[i][k] * B[k][j]
            C[i][j] = s
    return C


def write_input(path, A, B):
    n = len(A)
    lines = [str(n)]
    for row in A:
        lines.append(" ".join(str(x) for x in row))
    for row in B:
        lines.append(" ".join(str(x) for x in row))
    with open(path, "w") as f:
        f.write("\n".join(lines) + "\n")


def read_matrix(path):
    with open(path) as f:
        text = f.read()
    if text.startswith("\n") or text.endswith("\n\n"):
        raise AssertionError("%s has extra blank lines" % path)
    if not text.endswith("\n"):
        raise AssertionError("%s missing final newline" % path)
    rows = []
    for line in text.splitlines():
        if line.endswith(" "):
            raise AssertionError("%s has trailing space" % path)
        rows.append([int(x) for x in line.split(" ")])
    return rows


def run_case(name, A, B):
    if not os.path.isfile(BINARY):
        raise RuntimeError("compile lab1 first")
    n = len(A)
    expected = naive(A, B)
    work = tempfile.mkdtemp(prefix="ee538_lab1_")
    try:
        write_input(os.path.join(work, "input.txt"), A, B)
        subprocess.check_call([BINARY], cwd=work)
        m1 = read_matrix(os.path.join(work, "output_m1.txt"))
        m2 = read_matrix(os.path.join(work, "output_m2.txt"))
        with open(os.path.join(work, "output_q3.txt")) as f:
            q3 = f.read()
        parts = q3.strip().split(" ")
        if q3 != q3.strip() + "\n" or len(parts) != 2:
            raise AssertionError("%s: bad output_q3.txt %r" % (name, q3))
        int(parts[0])
        int(parts[1])
        if len(m1) != n or any(len(row) != n for row in m1):
            raise AssertionError("%s: Q1 size mismatch" % name)
        if m1 != expected:
            raise AssertionError("%s: Q1 != naive\nQ1=%s\nexp=%s" % (name, m1, expected))
        if m2 != expected:
            raise AssertionError("%s: Q2 != naive\nQ2=%s\nexp=%s" % (name, m2, expected))
        print("PASS %s n=%d" % (name, n))
    finally:
        shutil.rmtree(work)


def identity(n):
    return [[1 if i == j else 0 for j in range(n)] for i in range(n)]


def zeros(n):
    return [[0] * n for _ in range(n)]


def main():
    cases = [
        ("n1_pos", [[4]], [[-3]]),
        ("n2_mixed", [[1, -2], [0, 5]], [[3, 4], [-1, 2]]),
        (
            "n3_assignment",
            [[2, 5, 6], [3, 4, 7], [0, 2, 5]],
            [[1, 4, 6], [3, 2, 1], [9, 7, 8]],
        ),
        (
            "n4_ident",
            identity(4),
            [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]],
        ),
        (
            "n5_pad",
            [
                [1, -1, 0, 2, 3],
                [0, 4, -2, 1, 0],
                [5, 0, 0, -3, 1],
                [2, 2, 2, 2, 2],
                [-1, 0, 1, 0, -1],
            ],
            [
                [0, 1, 2, 3, 4],
                [1, 0, 1, 0, 1],
                [-2, -1, 0, 1, 2],
                [3, 3, 3, 3, 3],
                [0, 0, 0, 0, 1],
            ],
        ),
        (
            "n8",
            [[(i * 3 + j - 4) for j in range(8)] for i in range(8)],
            [[(i - j) for j in range(8)] for i in range(8)],
        ),
        ("n3_zero", zeros(3), [[1, 2, 3], [4, 5, 6], [7, 8, 9]]),
        ("n2_ident", identity(2), [[7, -8], [9, 10]]),
    ]

    failed = 0
    for name, A, B in cases:
        try:
            run_case(name, A, B)
        except Exception as exc:
            failed += 1
            print("FAIL %s: %s" % (name, exc))
    if failed:
        print("%d test(s) failed" % failed)
        return 1
    print("all local tests passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
