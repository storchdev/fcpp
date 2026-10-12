# 092.02 — `std::vector` reallocation invalidation: insert shifts elements: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `*it = 2 (expected 3)` | `*it = 2 (expected 3)` |
