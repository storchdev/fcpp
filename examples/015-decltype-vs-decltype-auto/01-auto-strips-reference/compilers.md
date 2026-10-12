# 015.01 — `decltype` vs. `decltype(auto)`: `auto` strips the reference: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `cells[0].n = 0` | `cells[0].n = 0` |
