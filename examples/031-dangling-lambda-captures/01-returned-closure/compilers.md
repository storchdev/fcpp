# 031 — Dangling lambda captures: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none at `-O0`; `-Wuninitialized` at `-O2` | none |
| No sanitizer, `-O0` | crashes (core dumped) | prints `32766` |
| No sanitizer, `-O2` | prints `1` | prints `-1847710056` |
| ASan `-O0` | `stack-use-after-return` | `stack-use-after-return` |
| ASan `-O1` | `stack-use-after-return` | `stack-use-after-scope` |
| ASan `-O2` | `stack-use-after-scope` | no report in my run |

The values printed without a sanitizer are different garbage per compiler and level, and ASan's report kind differs by level and compiler; at `-O2` clang++ ASan missed it while g++ caught it.
