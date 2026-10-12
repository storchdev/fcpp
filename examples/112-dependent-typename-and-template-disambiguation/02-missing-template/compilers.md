# 112.02 — Dependent `typename` and `template` disambiguation: missing `template`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`; see the table.

| | g++ | clang++ |
| --- | --- | --- |
| Diagnostic | warning "expected ‘template’ keyword before dependent template name [-Wmissing-template-keyword]", then errors "expected primary-expression before ‘int’" and "expected ‘,’ or ‘;’ before ‘int’" | error "use 'template' keyword to treat 'make' as a dependent template name" |

