# 104.03 — Algorithms with invalid ranges or iterators: `binary_search` on unsorted data: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `binary_search(4) = 1` and `binary_search(1) = 0` at `-O0` and `-O2`.
