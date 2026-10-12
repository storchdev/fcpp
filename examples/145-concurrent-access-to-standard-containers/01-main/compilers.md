# 145 — Concurrent access to standard containers: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).** No difference in kind: neither compiler warns, both give wrong sizes or crash at `-O0` and `-O2` (values vary per run), and TSan reports `data race` at `-O0`, `-O1` and `-O2` with both.

