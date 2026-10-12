# 121.02 — Throwing from destructors: implicit noexcept: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** Both warn at `-O0` and `-O2` with different flags, and both abort at run time with the same message.

| | g++ | clang++ |
| --- | --- | --- |
| Warning | "‘throw’ will always call ‘terminate’ [-Wterminate]" | "'~File' has a non-throwing exception specification but can still throw [-Wexceptions]" |

