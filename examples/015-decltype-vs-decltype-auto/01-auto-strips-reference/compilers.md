# 015.01 — `decltype` vs. `decltype(auto)`: `auto` strips the reference: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `cells[0].n = 0` at `-O0` and `-O2`.
