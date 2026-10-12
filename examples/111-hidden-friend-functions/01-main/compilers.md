# 111 — Hidden friend functions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Error | "‘inspect’ was not declared in this scope" | "use of undeclared identifier 'inspect'" |

