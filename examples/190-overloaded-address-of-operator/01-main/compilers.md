# 190 — Overloaded address-of operator: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++11 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `true` | `true` |
