# 179 — Compile-time vs. runtime computation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `square(n) = 25, square(5) = 25` | `square(n) = 25, square(5) = 25` |
