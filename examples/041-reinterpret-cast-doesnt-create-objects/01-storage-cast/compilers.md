# 041 — `reinterpret_cast` doesn't create objects: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=undefined`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| No sanitizer, `-O0` | crashes (core dumped) | crashes (core dumped) |
| No sanitizer, `-O2` | crashes (core dumped) | no output, exit status 0 |
| UBSan `-O0`, `-O1`, `-O2` | `runtime error: member call on address ... which does not point to an object of type 'Widget'`, then a null-load error | `SEGV on unknown address 0x000000000001` reported by UBSan, with no `runtime error` line |

Both detect it with `-fsanitize=undefined` (the checker accepts a sanitizer report or non-zero exit), but only g++ names the cause (the invalid-vptr check).
