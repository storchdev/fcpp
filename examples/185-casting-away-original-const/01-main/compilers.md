# 185 — Casting away const from an originally const object: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++98 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `limit=7, through reference=9` | `limit=7, through reference=9` |
