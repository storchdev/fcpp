# 141 — Mutex deadlock from inconsistent lock ordering: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).** No difference: neither compiler warns, both finish in a plain run, and TSan reports `lock-order-inversion (potential deadlock)` at `-O0`, `-O1` and `-O2` with both.

