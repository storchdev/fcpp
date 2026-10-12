# 100.02 — Strict weak ordering requirements: `map` with `less_equal`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `size = 2, count(1) = 0, find(1) fails` at `-O0` and `-O2`.
