# EE-538 Lab 1

- Author: Kuntian Tang
- USC email: ktang115@usc.edu

## Program summary

This program reads two n-by-n integer matrices from `input.txt` and writes:

- `output_m1.txt`: product from recursive simple divide-and-conquer (Q1)
- `output_m2.txt`: product from recursive Strassen (Q2)
- `output_q3.txt`: integer `clock()` ticks for Q1 then Q2

If n is not a power of two, A and B are zero-padded to the next power of two before recursion. Only the original n-by-n block is written. `std::vector` is not used; matrices are `int**`.

Default Q2 recurses to a 1-by-1 base case (mandatory). Extra credit uses a separate `--extra` path that does not change the three required output files.

## Compile

On CARC (Rocky Linux):

```bash
module load gcc/12.5.0
g++ -std=c++17 -Wall -Wextra -O2 ktang115lab1.cpp -o lab1
```

## Run (mandatory Q1/Q2/Q3)

Place `input.txt` in the current directory, then:

```bash
./lab1
```

## Extra credit

Strassen can stop at submatrix size `2^h x 2^h` and finish with naive multiplication. This path is only used when the program is invoked as:

```bash
./lab1 --extra
```

That writes `extra_credit_times.txt` (n=128, h = 3..7). Plot with:

```bash
python3 plot_extra_credit.py
```

which writes `extra_credit_h_vs_time.png`.

## Local correctness check (not submitted)

```bash
python3 verify_lab1.py
```

## References / citations

No external source code was copied. Q1/Q2 recurrences follow the EE-538 Lab 1 specification.

## Known concerns

- `output_q3.txt` stores raw `clock()` ticks (`end - start` as integers). For very small n the values may be `0 0`.
- The Lab 1 text writes `C22 = M1 + M2 + M3 + M6`. That sign is inconsistent with the rest of the given M1–M7 identities; the implementation uses `C22 = M1 - M2 + M3 + M6` so Q2 matches the naive product.
- Extra-credit timing is machine-dependent. On this CARC node with n=128, h=6 (cutoff 64) was 1151 ticks vs naive 1245. See `extra_credit_h_vs_time.png`.
