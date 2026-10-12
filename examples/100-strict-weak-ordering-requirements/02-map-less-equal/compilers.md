# 100.02 — Strict weak ordering requirements: `map` with `less_equal`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `size = 2, count(1) = 0, find(1) fails` | `size = 2, count(1) = 0, find(1) fails` |
