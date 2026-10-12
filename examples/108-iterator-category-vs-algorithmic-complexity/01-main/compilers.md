# 108 — Iterator category vs. algorithmic complexity: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `n = 65536: comparisons = 16, iterator steps = 131066` | `n = 65536: comparisons = 16, iterator steps = 131066` |
