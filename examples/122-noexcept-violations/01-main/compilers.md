# 122 — `noexcept` violations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** Both warn at `-O0` and `-O2` and abort at run time with the same message.

| | g++ | clang++ |
| --- | --- | --- |
| Warning | "‘throw’ will always call ‘terminate’ [-Wterminate]" | "'parse' has a non-throwing exception specification but can still throw [-Wexceptions]" |

