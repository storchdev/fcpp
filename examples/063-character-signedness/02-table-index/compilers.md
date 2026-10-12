# 063.02 — Character signedness: `char` as an array index: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wchar-subscripts`: "array subscript has type ‘char’" | `-Wchar-subscripts`: "array subscript is of type 'char'" |
| Plain run, `-O0` and `-O2` | prints `1` | prints `1` |
| ASan `-O0`, `-O1` | `stack-buffer-underflow` | `stack-buffer-underflow` |
| ASan `-O2` | `stack-buffer-underflow` | no report (no `counts` label in the `-O2` assembly; not investigated further) |
