# 053.01 — Mismatched allocation and deallocation: `new[]` with `delete`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).** Both warn with `-Wmismatched-new-delete` at `-O0` and `-O2`, both print `4` without a sanitizer, and ASan reports `alloc-dealloc-mismatch` under both compilers at every level.
