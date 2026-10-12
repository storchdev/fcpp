# 105 — Returning references from `std::min` and `std::max`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wdangling-reference` ("possibly dangling reference to a temporary") at `-O0` and `-O2`; `-Wdangling-pointer=` also at `-O2` | none |
| Plain run, `-O0` and `-O2` | `banana` | `banana` |
| ASan `-O0`, `-O1`, `-O2` | `stack-use-after-scope` | `stack-use-after-scope` |
