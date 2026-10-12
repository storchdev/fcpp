# 068 — Floating-point non-associativity: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` (also `-O2 -ffp-contract=off` and `-O2 -march=native`) | `(a + b) + c = 1` and `a + (b + c) = 0` | same |
| Output, `-O2 -ffast-math` | `1` for both groupings | `1` for both groupings |
