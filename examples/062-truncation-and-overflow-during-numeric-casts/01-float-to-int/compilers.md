# 062.01 — Truncation and overflow during numeric casts: floating point to integer: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=float-cast-overflow`, `-O0` and `-O2`; sanitizer also at `-O1`).** No difference: neither compiler warns (also with `-Wconversion`), both print `-2147483648` at `-O0` and `-O2`, and both report `1e+10 is outside the range of representable values of type 'int'` under the sanitizer at `-O0`, `-O1` and `-O2` (clang++ adds a `SUMMARY` line).
