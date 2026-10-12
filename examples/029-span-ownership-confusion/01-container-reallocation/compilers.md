# 029.01 — `std::span` ownership confusion: container reallocation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).** Neither compiler warns. Without a sanitizer both print a garbage number (different between compilers, levels and runs). ASan reports `heap-use-after-free` under both compilers at every level.
