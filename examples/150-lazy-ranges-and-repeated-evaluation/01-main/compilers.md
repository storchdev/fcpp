# 150 — Lazy ranges and repeated evaluation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `transform ran 8 times for 4 elements` at `-O0` and `-O2`.

