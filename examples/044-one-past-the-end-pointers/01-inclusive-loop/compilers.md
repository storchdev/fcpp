# 044 — One-past-the-end pointers: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| No sanitizer, `-O0` | prints `73738` | prints `73738` |
| No sanitizer, `-O2` | prints `10` | prints `14019864` |
| ASan `-O0` | `stack-buffer-overflow` | `stack-buffer-overflow` |
| ASan `-O1`, `-O2` | `stack-buffer-overflow` | no report in my runs |

The out-of-bounds read returns a different value per compiler and level, and clang++'s ASan stops reporting it once optimization is on, so this is another case verified with g++.
