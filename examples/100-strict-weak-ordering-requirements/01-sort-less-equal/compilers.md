# 100.01 — Strict weak ordering requirements: `sort` with `<=`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).** No difference: neither compiler warns, both print `sorted 100 elements` in a plain run at `-O0` and `-O2`, and ASan reports `heap-buffer-overflow` at `-O0`, `-O1` and `-O2` with both.
