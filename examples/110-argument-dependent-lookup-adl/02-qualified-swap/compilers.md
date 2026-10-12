# 110.02 — Argument-dependent lookup (ADL): qualified swap: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `custom swap calls = 0` | `custom swap calls = 0` |
