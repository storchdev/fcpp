# 035.02 — Range-based `for` over temporary objects: C++23, and the hoisted reference: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++23 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wdangling-reference` at `-O0`; `-Wdangling-pointer=` and `-Wdangling-reference` at `-O2` | none |
| No sanitizer, `-O0` | crashes (core dumped) | crashes (core dumped) |
| No sanitizer, `-O2` | no output, exit status 0 | crashes (core dumped) |
| ASan `-O0`, `-O1`, `-O2` | `stack-use-after-scope` | `stack-use-after-scope` |

The behavior in this case is the same as in 035.01; the case exists to show that `-std=c++23` does not extend this particular temporary.
