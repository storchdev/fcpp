# 038 — Returning a reference through multiple calls: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).** Neither compiler warns. Both crash (core dumped) without a sanitizer at `-O0` and `-O2`, and ASan reports `heap-use-after-free` under both at every level.
