# 113 — SFINAE vs. hard compilation errors: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Error | "request for member ‘size’ in ‘t’, which is of non-class type ‘const int’" (in instantiation of ‘auto describe(const T&) [with T = int]’) | "member reference base type 'const int' is not a structure or union" (note: in instantiation of function template specialization 'describe<int>') |

