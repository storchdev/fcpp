# 094.01 — `std::deque` invalidation rules: reference across a middle insert: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `second = 99 (expected 2)` | `second = 99 (expected 2)` |
