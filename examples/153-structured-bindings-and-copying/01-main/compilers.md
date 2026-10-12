# 153 — Structured bindings and copying: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `a = 1, b = 2 (expected 2 and 3)` | `a = 1, b = 2 (expected 2 and 3)` |
