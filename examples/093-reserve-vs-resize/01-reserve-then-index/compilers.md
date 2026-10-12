# 093.01 — `reserve()` vs. `resize()`: indexing after `reserve`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0`, `-O1` and `-O2`).** No difference: neither compiler warns.

| | g++ | clang++ |
| --- | --- | --- |
| Plain run `-O0` | aborts: libstdc++ assertion `__n < this->size()` failed | same |
| Plain run `-O1`, `-O2` | `size = 0`, then an empty line | same |
| `-O2 -D_GLIBCXX_ASSERTIONS` | aborts with the same assertion | same |
