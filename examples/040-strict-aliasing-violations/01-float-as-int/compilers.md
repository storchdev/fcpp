# 040 — Strict aliasing violations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` | `r=1073741824 x=1073741824` | `r=1073741824 x=1073741824` |
| Output, `-O2` (optimizer assumes `int*` and `float` do not alias) | `r=1 x=1073741824` | `r=1 x=1073741824` |
| Sanitizer | none exists for this | none exists for this |
