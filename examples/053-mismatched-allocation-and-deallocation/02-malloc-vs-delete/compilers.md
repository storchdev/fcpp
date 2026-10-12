# 053.02 — Mismatched allocation and deallocation: `malloc` with `delete`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-O0` and `-O2` | `-Wmismatched-new-delete` | none under `-Wall -Wextra` |
| Output without sanitizer | `1 2` | `1 2` |
| ASan, every level | `alloc-dealloc-mismatch` | `alloc-dealloc-mismatch` |
| `detection` in JSON | lists the g++ warning | lists no clang++ warning |
