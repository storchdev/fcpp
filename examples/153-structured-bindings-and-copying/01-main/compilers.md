# 153 — Structured bindings and copying: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `a = 1, b = 2 (expected 2 and 3)` at `-O0` and `-O2`.

