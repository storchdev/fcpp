# 133.01 — Sequential consistency misconceptions: store buffering: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** Both compilers show the permitted outcome; counts differ by run and by compiler.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Rounds with both loads 0 (of 200000), `-O0` | 0, 0, 0 | 194, 7677, 8388 |
| Rounds with both loads 0 (of 200000), `-O2` | 27983, 11755, 31645 | 853, 1083, 27763 |
| `good.cpp` (seq_cst), `-O0` and `-O2` | 0 | 0 |

