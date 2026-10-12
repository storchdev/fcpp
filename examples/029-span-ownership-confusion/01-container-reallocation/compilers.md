# 029.01 — `std::span` ownership confusion: container reallocation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer | garbage number (differs between compilers, levels and runs) | garbage number (differs between compilers, levels and runs) |
| ASan, every level | `heap-use-after-free` | `heap-use-after-free` |
