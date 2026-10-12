# 038 — Returning a reference through multiple calls: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run without sanitizer, `-O0` and `-O2` | crashes (core dumped) | crashes (core dumped) |
| ASan, every level | `heap-use-after-free` | `heap-use-after-free` |
