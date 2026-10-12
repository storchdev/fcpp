# 083.02 — Copy elision vs. actual moves: two candidate locals: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `construct 1`, `construct 2`, `move 1`, `got 1` | `construct 1`, `construct 2`, `move 1`, `got 1` |
