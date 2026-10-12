# 043.01 — Pointer arithmetic outside an array: indexing past a member array: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=undefined`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| No sanitizer, `-O0` | prints `110` | prints `110` |
| No sanitizer, `-O2` | prints `73738` | prints `110` |
| UBSan `-O0`, `-O1`, `-O2` | `index 4 out of bounds for type 'int [4]'` | `index 4 out of bounds for type 'const int[4]'` |
