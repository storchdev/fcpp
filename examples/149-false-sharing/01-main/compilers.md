# 149 — False sharing: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Adjacent layout, `-O0` and `-O2` | large slowdown (measured ranges in `explanation.md`; machine and load dependent) | large slowdown (measured ranges in `explanation.md`; machine and load dependent) |
