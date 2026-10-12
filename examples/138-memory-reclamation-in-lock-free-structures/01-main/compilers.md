# 138 — Memory reclamation in lock-free structures: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).** No difference: neither compiler warns, both print `popped 2` in a plain run, and ASan reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both.
