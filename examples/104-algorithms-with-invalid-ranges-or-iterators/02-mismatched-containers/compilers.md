# 104.02 — Algorithms with invalid ranges or iterators: mismatched containers: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).** No difference: neither compiler warns, both abort in a plain run with `munmap_chunk(): invalid pointer` at `-O0` and `-O2`, and ASan reports `SEGV on unknown address` at `-O0`, `-O1` and `-O2` with both.
