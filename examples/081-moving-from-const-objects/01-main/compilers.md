# 081 — Moving from `const` objects: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `copy` then `move` | `copy` then `move` |
| `clang-tidy` `performance-move-const-arg` | reported it (the only tool that did) | reported it (the only tool that did) |
