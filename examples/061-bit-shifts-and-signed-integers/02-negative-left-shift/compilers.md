# 061.02 — Bit shifts and signed integers: left shift of a negative value: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` and `-O2` | `-2` | `-2` |
| UBSan, `-std=c++17`, `-O0`, `-O1`, `-O2` | `left shift of negative value -1` | same message, plus a `SUMMARY` line |
| `-std=c++20 -fsanitize=undefined` | prints `-2`, reports nothing | prints `-2`, reports nothing |
