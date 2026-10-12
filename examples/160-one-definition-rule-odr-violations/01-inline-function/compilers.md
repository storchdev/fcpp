# 160 — One Definition Rule (ODR) violations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `20, 20` at `-O0` and `20, 30` at `-O2` for the order `bad.cpp bad_b.cpp`.

