# 042 — Misaligned accesses: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=undefined`, `-O0` and `-O2`).** Neither compiler warns, and both print `16` without a sanitizer at both levels. UBSan reports `load of misaligned address ... for type 'const uint32_t', which requires 4 byte alignment` under both compilers at `-O0`, `-O1` and `-O2` (g++ at line 8 col 59, clang++ at line 8 col 12).
