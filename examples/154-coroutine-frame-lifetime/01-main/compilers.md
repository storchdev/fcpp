# 154 — Coroutine frame lifetime: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).** The sanitizer coverage differs.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run `-O0` / `-O2` | `running`, `done = 0` | `running`, `done = 0` |
| ASan `-O0` | `heap-use-after-free` | `heap-use-after-free` |
| ASan `-O1`, `-O2` | `heap-use-after-free` | no report |

