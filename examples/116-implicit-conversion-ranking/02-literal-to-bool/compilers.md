# 116.02 — Implicit conversion ranking: literal to bool: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `put(bool)` at `-O0` and `-O2`.

