# 061.01 — Bit shifts and signed integers: shift count: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` and `-O2` | `1` | `1` |
| UBSan, `-O0`, `-O1`, `-O2` | `shift exponent 32 is too large for 32-bit type 'unsigned int'` | same message, plus a `SUMMARY` line |
