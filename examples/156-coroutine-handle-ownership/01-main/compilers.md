# 156 — Coroutine handle ownership: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).** The outcomes differ at higher optimization levels.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run `-O0` | aborts (core dump) | aborts (core dump) |
| Plain run `-O2` | aborts (core dump) | `running`, exit 0 |
| ASan `-O0` | `heap-use-after-free` | `heap-use-after-free` |
| ASan `-O1`, `-O2` | `heap-use-after-free` | no report |

