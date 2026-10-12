# 125.02 — Constructor exceptions and partial object destruction: leaked member: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).** Both compilers build it silently; only the sanitizer detail differs.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| ASan (`-O0`, `-O1`, `-O2`) | `LeakSanitizer: detected memory leaks` at all three levels | leak reported at `-O0` only; nothing at `-O1`, `-O2` |

