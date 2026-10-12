# 099.01 — `insert`, `emplace`, and `try_emplace` semantics: `insert` keeps the old value: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `m[1] = 10 (wanted 99)` at `-O0` and `-O2`.
