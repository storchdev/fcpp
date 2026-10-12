# 051 — Struct padding and object representations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `fields equal: 1, memcmp equal: 0` | `fields equal: 1, memcmp equal: 0` |
