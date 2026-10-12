# 089 — `weak_ptr` check-then-use races: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run `-O0` | crashes (core dumped) | crashes (core dumped) |
| Plain run `-O2` | crashes (core dumped) | prints `value = 42` |
| UBSan `-O0`, `-O1`, `-O2` | `member access within null pointer of type 'struct element_type'` | `member access within null pointer of type 'element_type' (aka 'Data')` |
