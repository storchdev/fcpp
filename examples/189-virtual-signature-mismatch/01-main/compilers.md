# 189 — Virtual signature mismatch: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++11 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-Wall -Wextra` | `-Woverloaded-virtual` | `-Woverloaded-virtual` |
| Output, `-O0` and `-O2` | `3` | `3` |
