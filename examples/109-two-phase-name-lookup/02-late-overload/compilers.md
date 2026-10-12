# 109.02 — Two-phase name lookup: late overload: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `f(double)` at `-O0` and `-O2`.

