# 062.01 — Truncation and overflow during numeric casts: floating point to integer: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=float-cast-overflow`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings (also with `-Wconversion`) | none | none |
| Output without sanitizer, `-O0` and `-O2` | `-2147483648` | `-2147483648` |
| `-fsanitize=float-cast-overflow`, `-O0`, `-O1`, `-O2` | `1e+10 is outside the range of representable values of type 'int'` | same message, plus a `SUMMARY` line |
