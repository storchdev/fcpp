# 086 — Double ownership with `std::shared_ptr`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run, `-O0` and `-O2` | `free(): double free detected in tcache 2`, aborts | same |
| ASan `-O0`, `-O1`, `-O2` | `attempting double-free` (summary names `bad.cpp:14`) | `attempting double-free` (summary names a binary offset) |
