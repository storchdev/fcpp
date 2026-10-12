# 029.02 — `std::span` ownership confusion: a span of a temporary container: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).** Both print `7` without a sanitizer, and ASan reports `heap-use-after-free` under both compilers at every level. clang++ also warns at compile time (`-Wdangling-gsl`, `object backing the pointer will be destroyed at the end of the full-expression`, line 11) at `-O0` and `-O2`; g++ has no warning.
