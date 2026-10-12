# 053.01 — Mismatched allocation and deallocation: `new[]` with `delete`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-O0` and `-O2` | `-Wmismatched-new-delete` | `-Wmismatched-new-delete` |
| Output without sanitizer | `4` | `4` |
| ASan, every level | `alloc-dealloc-mismatch` | `alloc-dealloc-mismatch` |
