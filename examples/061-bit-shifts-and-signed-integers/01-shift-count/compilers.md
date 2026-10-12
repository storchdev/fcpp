# 061.01 — Bit shifts and signed integers: shift count: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).** No difference: neither compiler warns, both print `1` at `-O0` and `-O2`, and both report `shift exponent 32 is too large for 32-bit type 'unsigned int'` under UBSan at `-O0`, `-O1` and `-O2` (clang++ adds a `SUMMARY` line).
