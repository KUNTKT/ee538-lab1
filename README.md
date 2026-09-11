# EE-538 Lab 1

## Name

Kuntian Tang

## USC ID

4855814938

## USC email

ktang115@usc.edu

## Summary

This program reads two n-by-n integer matrices from `input.txt` and writes:

- `output_m1.txt`: product from recursive simple divide-and-conquer (Q1)
- `output_m2.txt`: product from recursive Strassen (Q2)
- `output_q3.txt`: integer `clock()` ticks for Q1 then Q2

If n is not a power of two, A and B are zero-padded to the next power of two before recursion. Only the original n-by-n block is written. `std::vector` is not used; matrices are `int**`.

Default Q2 recurses to a 1-by-1 base case (mandatory). Extra credit uses a separate `--extra` path that does not change the three required output files.

Submitted assignment files use the required `[USC ID] + [assignment filename]` names:

- `4855814938lab1.cpp`
- `4855814938output_m1.txt`
- `4855814938output_m2.txt`
- `4855814938output_q3.txt`
- `readme.pdf`

The program still reads `input.txt` and writes `output_m1.txt`, `output_m2.txt`, and `output_q3.txt` at runtime.

## References

No external source code was copied. Q1/Q2 recurrences follow the EE-538 Lab 1 specification. Extra-credit cutoff timing is measured with `clock()` on a CARC Rocky Linux node.

Known notes:

- `output_q3.txt` stores raw `clock()` ticks (`end - start` as integers). For very small n the values may be `0 0`.
- The Lab 1 text writes `C22 = M1 + M2 + M3 + M6`. That sign is inconsistent with the rest of the given M1–M7 identities; the implementation uses `C22 = M1 - M2 + M3 + M6` so Q2 matches the naive product.
- Extra-credit timing is machine-dependent. On this CARC node with n=128, h=6 (cutoff 64) was 1151 ticks vs naive 1245.

## Run instructions

On CARC (Rocky Linux):

```bash
module load gcc/12.5.0
g++ -std=c++17 -Wall -Wextra -O2 4855814938lab1.cpp -o lab1
```

Place `input.txt` in the current directory, then:

```bash
./lab1
```

This writes `output_m1.txt`, `output_m2.txt`, and `output_q3.txt`. The copies submitted in this repository are named `4855814938output_m1.txt`, `4855814938output_m2.txt`, and `4855814938output_q3.txt`.

Optional extra credit (does not change the three required outputs):

```bash
./lab1 --extra
python3 plot_extra_credit.py
```

Local correctness check (not submitted):

```bash
python3 verify_lab1.py
```
