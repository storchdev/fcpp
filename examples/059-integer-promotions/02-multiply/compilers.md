# 059.02 — Integer promotions: `uint16_t * uint16_t`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).** No difference: neither compiler warns, both print `4294836225` at `-O0` and `-O2`, and both report `signed integer overflow: 65535 * 65535 cannot be represented in type 'int'` under UBSan at `-O0`, `-O1` and `-O2`. (g++ prints only the `runtime error` line; clang++ also prints a `SUMMARY` line.)
