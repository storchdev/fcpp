# 132 — Release/acquire synchronization: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer | `payload = 42, copy = 42` | `payload = 42, copy = 42` |
| TSan, `-O0`, `-O1`, `-O2` | `data race` | `data race` |
