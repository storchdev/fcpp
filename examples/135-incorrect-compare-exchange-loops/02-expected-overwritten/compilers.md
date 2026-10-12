# 135.02 — Incorrect compare-exchange loops: `expected` is overwritten: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `lost the race; state was 0, but expected now reads 5` | `lost the race; state was 0, but expected now reads 5` |
