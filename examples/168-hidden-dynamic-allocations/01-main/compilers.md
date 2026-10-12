# 168 — Hidden dynamic allocations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `allocations = 1000` (the good version prints `allocations = 0`) | `allocations = 1000` (the good version prints `allocations = 0`) |
