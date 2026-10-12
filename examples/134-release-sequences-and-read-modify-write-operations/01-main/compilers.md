# 134 — Release sequences and read-modify-write operations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer | `payload = 42` | `payload = 42` |
| TSan, `-O0`, `-O1`, `-O2` | no report | no report |
