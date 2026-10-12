# 080 — Use-after-move assumptions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `sent 'hello'`, `after move: text size=0 priority=7 pending=1`, `sent ''` at `-O0` and `-O2`. Only `clang-tidy` (`bugprone-use-after-move`) reported it.
