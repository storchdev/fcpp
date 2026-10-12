# 119.03 — `constexpr`, `consteval`, and `constinit`: constinit initializer: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Error | "‘constinit’ variable ‘g’ does not have a constant initializer" (plus "call to non-‘constexpr’ function ‘int runtime_value()’") | "variable does not have a constant initializer" |

