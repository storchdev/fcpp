# 053.02 — Mismatched allocation and deallocation: `malloc` with `delete`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).** g++ warns (`-Wmismatched-new-delete`) at `-O0` and `-O2`; clang++ does not warn under `-Wall -Wextra`. Both print `1 2` without a sanitizer, and ASan reports `alloc-dealloc-mismatch` under both compilers at every level. That is why `detection` lists the g++ warning but no clang++ warning for this case.
