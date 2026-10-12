# 003 — Brace initialization vs. parentheses: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra -Wpedantic`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings or errors | none | none |
| Output, `-O0` and `-O2` | `a.size=3 b.size=2 c.size=5 d.size=1` and `s.size=3 t.size=2` | same |
