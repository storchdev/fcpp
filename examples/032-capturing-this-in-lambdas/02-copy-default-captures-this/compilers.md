# 032.02 — Capturing `this` in lambdas: `[=]` does not copy members: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `snapshot sees 99` at `-O0` and `-O2`.
