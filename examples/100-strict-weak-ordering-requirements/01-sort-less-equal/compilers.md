# 100.01 — Strict weak ordering requirements: `sort` with `<=`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` and `-O2` | `sorted 100 elements` | `sorted 100 elements` |
| ASan, `-O0`, `-O1`, `-O2` | `heap-buffer-overflow` | `heap-buffer-overflow` |
