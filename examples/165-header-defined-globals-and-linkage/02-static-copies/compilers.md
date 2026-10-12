# 165.02 — Header-defined globals and linkage: static copies: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `counter = 0 (expected 1)` at `-O0` and `-O2`.

