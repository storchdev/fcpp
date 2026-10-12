# 008.01 — Null pointer overload resolution: `0`, `NULL`, `nullptr`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both print `report(int)`, `assign(long)`, `assign(const char*)` at both levels. g++ warns about the `NULL` call (`passing NULL to non-pointer argument 1 of 'void assign(long int)' [-Wconversion-null]`, line 13); clang++ emits no warning for the same line under `-Wall -Wextra`.
