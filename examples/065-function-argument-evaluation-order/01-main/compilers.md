# 065 — Function argument evaluation order: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output at `-O0` and `-O2` | `a = 2, b = 1` | `a = 1, b = 2` |
