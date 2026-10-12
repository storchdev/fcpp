# 146.01 — Atomic reference-counting misconceptions: the shared object: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).** The compilers differ only in what TSan sees at `-O2`.

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Plain run `-O0` | `*p = 118312` | `*p = 136569` |
| Plain run `-O2` | `*p = 200000` | `*p = 200000` |
| TSan `-O0`, `-O1` | `data race` | `data race` |
| TSan `-O2` | no report | `data race` |

