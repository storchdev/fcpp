# 141 — Mutex deadlock from inconsistent lock ordering: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run without sanitizer | finishes | finishes |
| TSan, `-O0`, `-O1`, `-O2` | `lock-order-inversion (potential deadlock)` | `lock-order-inversion (potential deadlock)` |
