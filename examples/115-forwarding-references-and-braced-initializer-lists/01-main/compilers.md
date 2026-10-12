# 115 — Forwarding references and braced initializer lists: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Error | "no matching function for call to ‘take(<brace-enclosed initializer list>)’" | "no matching function for call to 'take'" |

