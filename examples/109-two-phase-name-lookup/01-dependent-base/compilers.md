# 109.01 — Two-phase name lookup: dependent base: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Error | "there are no arguments to ‘hello’ that depend on a template parameter, so a declaration of ‘hello’ must be available [-Wtemplate-body]" | "use of undeclared identifier 'hello'" |

