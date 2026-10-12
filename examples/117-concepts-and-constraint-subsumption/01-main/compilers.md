# 117 — Concepts and constraint subsumption: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Error | "call of overloaded ‘f(int)’ is ambiguous" | "call to 'f' is ambiguous" |

