# 068 — Floating-point non-associativity: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `(a + b) + c = 1` and `a + (b + c) = 0` at `-O0` and `-O2`, also with `-O2 -ffp-contract=off` and `-O2 -march=native`. With `-O2 -ffast-math` both print `1` for both groupings.
