# 119.01 — `constexpr`, `consteval`, and `constinit`: consteval with a runtime argument: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Error | "call to consteval function ‘square(n)’ is not a constant expression" | "call to consteval function 'square' is not a constant expression" |

