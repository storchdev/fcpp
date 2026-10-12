# 093.02 — `reserve()` vs. `resize()`: `push_back` after `resize`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `size = 6: 0 0 0 1 2 3` at `-O0` and `-O2`.
