# 033.01 — Dangling `c_str()` and `data()` pointers: modification: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer | garbage bytes | garbage bytes |
| ASan, every level | `heap-use-after-free` | `heap-use-after-free` |
