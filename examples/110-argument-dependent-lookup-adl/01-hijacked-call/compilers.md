# 110.01 — Argument-dependent lookup (ADL): hijacked call: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `lib::show(Widget)` at `-O0` and `-O2`.

