# 133.02 — Sequential consistency misconceptions: plain data: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer | `turn = 2, shared_total = 2` | `turn = 2, shared_total = 2` |
| TSan, `-O0`, `-O1`, `-O2` | `data race` | `data race` |
