# 067.02 — Conditional operator type deduction: a copy, not an alias: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `r = original, s = changed` at `-O0` and `-O2`.
