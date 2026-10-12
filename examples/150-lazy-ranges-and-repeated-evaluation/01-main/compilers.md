# 150 — Lazy ranges and repeated evaluation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `transform ran 8 times for 4 elements` | `transform ran 8 times for 4 elements` |
