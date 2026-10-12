# 004 — Initializer-list constructor preference: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra -Wpedantic`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | the same six lines | the same six lines |
| Extra test: `struct W { W(int, double); W(std::initializer_list<int>); }; W w{10, 5.0};` | error: `narrowing conversion of '5.0e+0' from 'double' to 'int' [-Wnarrowing]` | error: `type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]` |
