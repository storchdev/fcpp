# 059.02 — Integer promotions: `uint16_t * uint16_t`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` and `-O2` | `4294836225` | `4294836225` |
| UBSan, `-O0`, `-O1`, `-O2` | `signed integer overflow: 65535 * 65535 cannot be represented in type 'int'` (`runtime error` line only) | same message, plus a `SUMMARY` line |
