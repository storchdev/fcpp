# 179 — Compile-time vs. runtime computation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `square(n) = 25, square(5) = 25` at `-O0` and `-O2`.

