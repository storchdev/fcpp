# 030 — `std::initializer_list` backing-array lifetime: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none at `-O0`; `-Wdangling-pointer=` and `-Wuninitialized` at `-O2` | none |
| No sanitizer, `-O0` | prints `1` | prints `1` |
| No sanitizer, `-O2` | prints `32764` | prints `1` |
| ASan `-O0` | `stack-use-after-scope` | `stack-use-after-scope` |
| ASan `-O1`, `-O2` | `stack-use-after-scope` | no report in my runs |

So ASan detects this with g++ at every level but with clang++ only at `-O0`, and `1` is the "right-looking" answer that clang++ prints even at `-O2`, where g++ prints a different number.
