# 082 — Pessimizing moves on return: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings, `-O0` and `-O2` | `-Wpessimizing-move`: moving a local object in a return statement prevents copy elision (column on the argument) | `-Wpessimizing-move`: same text (column on the `std::move` call) |
| Output, `-O0` and `-O2` | `construct` then `move` | `construct` then `move` |
