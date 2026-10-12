# 099.01 — `insert`, `emplace`, and `try_emplace` semantics: `insert` keeps the old value: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `m[1] = 10 (wanted 99)` | `m[1] = 10 (wanted 99)` |
