# 131 — `memory_order_relaxed` misuse: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).** No difference: neither compiler warns, both print `payload = 42` in a plain run at `-O0` and `-O2`, and TSan reports `data race` at `-O0`, `-O1` and `-O2` with both.

