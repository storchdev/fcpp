# 096.02 — Past-the-end iterator invalidation: `erase`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `2 3 4 4` at `-O0` and `-O2`.
