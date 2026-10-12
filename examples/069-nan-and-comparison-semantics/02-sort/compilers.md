# 069.02 — NaN and comparison semantics: `std::sort` with NaN: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `0 1 2 3 4 5 6 7 9 nan 8 nan 10 11 12 13 14 15 16 17` and `is_sorted: 1` | `0 1 2 3 4 5 6 7 9 nan 8 nan 10 11 12 13 14 15 16 17` and `is_sorted: 1` |
