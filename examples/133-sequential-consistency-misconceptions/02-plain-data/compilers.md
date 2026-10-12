# 133.02 — Sequential consistency misconceptions: plain data: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).** No difference: neither compiler warns, both print `turn = 2, shared_total = 2` in a plain run, and TSan reports `data race` at `-O0`, `-O1` and `-O2` with both.

