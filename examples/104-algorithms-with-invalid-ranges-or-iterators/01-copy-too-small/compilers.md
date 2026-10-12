# 104.01 — Algorithms with invalid ranges or iterators: `copy` into a too-small destination: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings at `-O0` | none | none |
| Warnings at `-O2` | `-Warray-bounds=` ("forming offset [8, 15] is out of the bounds [0, 8]") | none |
| Plain run | `dst[0] = 1` | `dst[0] = 1` |
| ASan `-O0`, `-O1`, `-O2` | `heap-buffer-overflow` | `heap-buffer-overflow` |
