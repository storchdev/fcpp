# 061.02 — Bit shifts and signed integers: left shift of a negative value: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).** No difference: neither compiler warns, both print `-2` at `-O0` and `-O2`, and both report `left shift of negative value -1` under UBSan at `-O0`, `-O1` and `-O2` (clang++ adds a `SUMMARY` line). With `-std=c++20 -fsanitize=undefined` both print `-2` and report nothing.
