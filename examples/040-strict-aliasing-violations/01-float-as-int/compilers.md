# 040 — Strict aliasing violations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference between the compilers: neither warns, and both print `r=1073741824 x=1073741824` at `-O0` and `r=1 x=1073741824` at `-O2`. The `-O2` result is the optimizer assuming `int*` and `float` do not alias; there is no sanitizer for this.
