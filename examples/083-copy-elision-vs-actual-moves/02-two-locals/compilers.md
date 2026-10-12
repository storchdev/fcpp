# 083.02 — Copy elision vs. actual moves: two candidate locals: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `construct 1`, `construct 2`, `move 1`, `got 1` at `-O0` and `-O2`.
