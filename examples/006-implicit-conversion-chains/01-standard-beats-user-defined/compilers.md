# 006.01 — Implicit conversion chains: a standard conversion beats a user-defined one: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra -Wpedantic`, `-O0` and `-O2`).** No difference: both print `bool: 1` then `string: disk full` at both levels, and neither warns.
