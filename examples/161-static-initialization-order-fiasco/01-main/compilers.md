# 161 — Static initialization order fiasco: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** The outcome depends on the compiler at `-O2`.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Order `bad.cpp bad_b.cpp`, `-O0` | `derived = 1` | `derived = 1` |
| Order `bad.cpp bad_b.cpp`, `-O2` | `derived = 1` | `derived = 6` |
| Order `bad_b.cpp bad.cpp`, `-O0` and `-O2` | `derived = 6` | `derived = 6` |

