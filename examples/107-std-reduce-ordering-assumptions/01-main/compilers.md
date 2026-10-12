# 107 — `std::reduce` ordering assumptions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `reduce = 100, accumulate = 64` | `reduce = 100, accumulate = 64` |
| Standard library | libstdc++ | libstdc++ |
