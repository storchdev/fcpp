# 012.02 — CTAD: string literals deduce as `const char*`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `names[0] == input.c_str()? 0 (address comparison)` | `names[0] == input.c_str()? 0 (address comparison)` |
