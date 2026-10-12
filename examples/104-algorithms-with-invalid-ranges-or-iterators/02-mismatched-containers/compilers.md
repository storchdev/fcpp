# 104.02 — Algorithms with invalid ranges or iterators: mismatched containers: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run without sanitizer, `-O0` and `-O2` | aborts with `munmap_chunk(): invalid pointer` | aborts with `munmap_chunk(): invalid pointer` |
| ASan, `-O0`, `-O1`, `-O2` | `SEGV on unknown address` | `SEGV on unknown address` |
