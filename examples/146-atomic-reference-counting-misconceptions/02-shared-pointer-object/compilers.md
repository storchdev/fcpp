# 146.02 — Atomic reference-counting misconceptions: the `shared_ptr` object: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| TSan, `-O0`, `-O1`, `-O2` | `data race` | `data race` |
