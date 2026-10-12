# 146.02 — Atomic reference-counting misconceptions: the `shared_ptr` object: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).** No difference: neither compiler warns, and TSan reports `data race` at `-O0`, `-O1` and `-O2` with both.

