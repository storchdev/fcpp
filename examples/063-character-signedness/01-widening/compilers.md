# 063.01 — Character signedness: widening and comparison: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wtype-limits`: "comparison is always false due to limited range of data type" | `-Wtautological-constant-out-of-range-compare`: "result of comparison of constant 233 with expression of type 'char' is always false" |
| Output at `-O0` and `-O2` | `widened = -23`, `c != 0xE9` | same |
| With `-funsigned-char` | `widened = 233`, `c == 0xE9`, no warning | same |
