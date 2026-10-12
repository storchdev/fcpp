# 029.02 — `std::span` ownership confusion: a span of a temporary container: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-O0` and `-O2` | none | `-Wdangling-gsl`: `object backing the pointer will be destroyed at the end of the full-expression` (line 11) |
| Output without sanitizer | `7` | `7` |
| ASan, every level | `heap-use-after-free` | `heap-use-after-free` |
