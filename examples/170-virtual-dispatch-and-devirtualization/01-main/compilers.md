# 170 — Virtual dispatch and devirtualization: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** The sizes differ by compiler at `-O2`; ms for 100000000 calls, three runs.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| `bad.cpp` `-O0` | 741–743 | 752–754 |
| `good.cpp` `-O0` | 98–107 | 141–142 |
| `bad.cpp` `-O2` | 39 | 98 |
| `good.cpp` `-O2` | 19–24 | 15 |

