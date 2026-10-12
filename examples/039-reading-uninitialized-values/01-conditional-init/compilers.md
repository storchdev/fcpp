# 039 — Reading uninitialized values: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=memory`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| No sanitizer, `-O0` | prints `privileged port` | prints `privileged port` |
| No sanitizer, `-O2` | prints `privileged port` | prints `unprivileged port` |
| MemorySanitizer | `-fsanitize=memory` is rejected (`unrecognized argument`) | `use-of-uninitialized-value` at `-O0`, `-O1`, `-O2` |

The same source takes opposite branches under the two compilers at `-O2`. Only clang++'s MemorySanitizer reports it, which is why the checker builds this case with clang++.
