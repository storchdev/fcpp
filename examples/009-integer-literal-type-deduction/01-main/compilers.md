# 009 — Integer literal type deduction: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Output, `-O0` and `-O2` | `2147483647  : int`, `2147483648  : long`, `0x80000000  : unsigned int`, `-2147483648 : long`, `-1 < 4294967295` | same |
| Warning, line 18 (`-Wsign-compare`) | `comparison of integer expressions of different signedness` | `comparison of integers of different signs` |
| Warning, line 19 (always-true comparison) | `-Wtype-limits` | `-Wtautological-constant-out-of-range-compare` |
