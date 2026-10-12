# 064.01 — Unsequenced side effects: two increments of one variable: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wsequence-point`: "operation on ‘i’ may be undefined" | `-Wunsequenced`: "multiple unsequenced modifications to 'i'" |
| Output at `-O0` and `-O2` | `r = 4, i = 3` | `r = 4, i = 3` |
