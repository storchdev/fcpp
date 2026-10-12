# 180 — Floating-point prices and exact comparisons: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `total = 0.99999999999999989, total == 1.00: 0` and `0.1 + 0.2 == 0.3: 0` at `-O0` and `-O2`.

