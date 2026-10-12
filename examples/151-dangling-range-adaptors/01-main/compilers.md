# 151 — Dangling range adaptors: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).** The sanitizer's report kind and coverage differ.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run `-O0` / `-O2` | garbage / garbage | garbage / nothing (exit status 232) |
| ASan `-O0` | `stack-use-after-return` | `stack-use-after-return` |
| ASan `-O1` | `stack-use-after-return` | `heap-use-after-free` |
| ASan `-O2` | `stack-use-after-return` | no report |

