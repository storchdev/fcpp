# 016 — Parentheses changing `decltype` results: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `before = 99` at `-O0` and `-O2`.
