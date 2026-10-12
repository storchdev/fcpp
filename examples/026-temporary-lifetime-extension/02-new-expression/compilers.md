# 026.02 — Temporary lifetime extension: a `new` expression: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none at `-O0`; at `-O2` `-Wdangling-pointer=` and `-Wuninitialized` (inside `<bits/basic_string.h>`) | `-Wdangling-field` at `-O0` and `-O2` (`temporary bound to reference member of allocated object will be destroyed at the end of the full-expression`) |
| No sanitizer | prints the long string, then garbage at `-O0` and an empty second line at `-O2` | prints the long string, then garbage |
| ASan `-O0`, `-O1`, `-O2` | `stack-use-after-scope` | `stack-use-after-scope` |

g++ warns only at `-O2`, clang++ at both levels, so the warnings are not a substitute for ASan. The checker's `detection` lists only the sanitizer for this case.
