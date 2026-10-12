# 160 — One Definition Rule (ODR) violations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, order `bad.cpp bad_b.cpp`, `-O0` | `20, 20` | `20, 20` |
| Output, order `bad.cpp bad_b.cpp`, `-O2` | `20, 30` | `20, 30` |
