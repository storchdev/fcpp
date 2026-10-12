# 110.01 — Argument-dependent lookup (ADL): hijacked call: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `lib::show(Widget)` | `lib::show(Widget)` |
