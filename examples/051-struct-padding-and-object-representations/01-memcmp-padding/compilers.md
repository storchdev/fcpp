# 051 — Struct padding and object representations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `fields equal: 1, memcmp equal: 0` at `-O0` and `-O2`.
