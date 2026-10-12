# 012.02 — CTAD: string literals deduce as `const char*`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `names[0] == input.c_str()? 0 (address comparison)` at `-O0` and `-O2`.
