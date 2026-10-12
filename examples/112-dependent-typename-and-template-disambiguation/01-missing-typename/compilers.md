# 112.01 — Dependent `typename` and `template` disambiguation: missing `typename`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Error | "need ‘typename’ before ‘C::value_type’ because ‘C’ is a dependent scope [-Wtemplate-body]", then "‘first’ was not declared in this scope" | "missing 'typename' prior to dependent type name 'C::value_type'" |

