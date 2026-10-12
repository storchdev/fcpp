# 026.01 — Temporary lifetime extension: through a function return: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wdangling-reference` at `-O0` and `-O2`; at `-O2` also `-Wdangling-pointer=` and `-Wuninitialized` (both reported inside `<bits/basic_string.h>`) | none at either level |
| No sanitizer | prints the long string, then garbage bytes for the second line (differs between `-O0` and `-O2`) | prints the long string, then garbage bytes |
| ASan `-O0`, `-O1`, `-O2` | `stack-use-after-scope` | `stack-use-after-scope` |

Both sanitizers catch it at every level; only g++ warns at compile time.
