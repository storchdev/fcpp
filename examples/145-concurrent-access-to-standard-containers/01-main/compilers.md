# 145 — Concurrent access to standard containers: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run, `-O0` and `-O2` | wrong sizes or a crash (values vary per run) | wrong sizes or a crash (values vary per run) |
| TSan, `-O0`, `-O1`, `-O2` | `data race` | `data race` |
