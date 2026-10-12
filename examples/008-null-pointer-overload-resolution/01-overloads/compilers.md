# 008.01 — Null pointer overload resolution: `0`, `NULL`, `nullptr`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Output, `-O0` and `-O2` | `report(int)`, `assign(long)`, `assign(const char*)` | same |
| Warning, line 13 (`NULL` call) | `-Wconversion-null`: `passing NULL to non-pointer argument 1 of 'void assign(long int)'` | none under `-Wall -Wextra` |
