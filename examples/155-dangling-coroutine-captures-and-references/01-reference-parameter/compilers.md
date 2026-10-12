# 155.01 — Dangling coroutine captures and references: reference parameter: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).** Both detect it; the report kind differs at `-O2`.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run `-O0` / `-O2` | garbage after `hello ` | garbage after `hello ` |
| ASan `-O0`, `-O1` | `stack-use-after-scope` | `stack-use-after-scope` |
| ASan `-O2` | `stack-use-after-scope` | `heap-use-after-free` |

