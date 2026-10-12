# 002 — The most vexing parse: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wvexing-parse` at line 16: `parentheses were disambiguated as a function declaration` | `-Wvexing-parse` at line 16: same text |
| Output, `-O0` and `-O2` | `t is a function: 1` | `t is a function: 1` |
