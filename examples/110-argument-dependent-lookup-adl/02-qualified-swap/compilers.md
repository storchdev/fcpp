# 110.02 — Argument-dependent lookup (ADL): qualified swap: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `custom swap calls = 0` at `-O0` and `-O2`.

