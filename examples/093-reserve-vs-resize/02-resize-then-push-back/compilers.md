# 093.02 — `reserve()` vs. `resize()`: `push_back` after `resize`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `size = 6: 0 0 0 1 2 3` | `size = 6: 0 0 0 1 2 3` |
