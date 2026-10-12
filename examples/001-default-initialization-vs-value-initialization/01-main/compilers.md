# 001 — Default initialization vs. value initialization: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`).** Both compilers build and run the program, and they disagree on diagnostics and on what the indeterminate values look like:

| | g++ | clang++ |
| --- | --- | --- |
| `-Wuninitialized` | warns for `p.x` and `p.y` at `-O0`, `-O1` and `-O2`; also for the `new int[4]` read at `-O1` and `-O2` (`'*(int*)<unknown>' is used uninitialized`) | no warning at any of the three levels |
| `p` / `buf[0]` at `-O0` | `(-867534257, 32763)` / `0` | `(1, 0)` / `0` |
| `p` / `buf[0]` at `-O1` | `(0, 0)` / `0` | `(-697524048, 0)` / `-697524047` |
| `p` / `buf[0]` at `-O2` | `(0, 0)` / `0` | `(-1946619712, 0)` / `-1946619711` |
| MemorySanitizer | `-fsanitize=memory` is rejected (`unrecognized argument to '-fsanitize=' option: 'memory'`) | `use-of-uninitialized-value` at line 18 |
| AddressSanitizer, UBSan | no report | no report |

The numbers are single runs and vary between runs, so only the pattern is meaningful: g++ printed zeros for `p` at `-O1`/`-O2` where clang++ printed leftover stack values. A reviewer using g++ gets the warning, one using clang++ gets nothing at compile time and needs MemorySanitizer. That is why `detection` lists both `warning:g++:-Wuninitialized` and `sanitizer:memory`, and why the checker builds this case with clang++.
