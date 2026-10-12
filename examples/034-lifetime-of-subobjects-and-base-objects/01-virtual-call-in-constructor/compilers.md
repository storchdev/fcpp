# 034.01 — Lifetime of subobjects and base objects: a virtual call in a base constructor: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `Shape::describe` then `Circle::describe` | `Shape::describe` then `Circle::describe` |
