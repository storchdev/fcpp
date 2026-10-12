# 057 — Unsigned arithmetic wraparound: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wtype-limits`: "comparison of unsigned expression in ‘>= 0’ is always true" (at `-O0` and `-O2`) | none; `-Wtautological-unsigned-zero-compare` (not in `-Wall -Wextra`) reports "result of comparison of unsigned expression >= 0 is always true" |
| Output at `-O0` and `-O2` | `last_index(empty) = 18446744073709551615`, then `i = 3, 2, 1, 0, 4294967295, 4294967294` | same |
