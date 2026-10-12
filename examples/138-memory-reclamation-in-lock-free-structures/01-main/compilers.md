# 138 — Memory reclamation in lock-free structures: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer | `popped 2` | `popped 2` |
| ASan, `-O0`, `-O1`, `-O2` | `heap-use-after-free` | `heap-use-after-free` |
